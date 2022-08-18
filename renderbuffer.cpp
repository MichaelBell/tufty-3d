#include "common.h"
#include "renderbuffer.h"
#include "hardware/dma.h"
#include "pico/scanvideo.h"
#include "pico/scanvideo/composable_scanline.h"

using namespace pimoroni;

RenderBuffer::RenderBuffer(uint16_t width, uint16_t height, void *frame_buffer)
    : PicoGraphics(width, height, frame_buffer)
    , width_per_run(width / RUNS_PER_LINE)
{
    assert((width % RUNS_PER_LINE) == 0);
    assert(4 * width_per_run < 256);

    pen_type = PEN_1BIT;  // Anything that gets scanline convert called on it.
    if (this->frame_buffer == nullptr) {
        this->frame_buffer = (void *)(new PixelRun[height * RUNS_PER_LINE * 2]);
    }
    
    // Scanvideo is evil and just randomly uses low channel numbers, so we choose a higher number...
    clear_dma_channel = 6; dma_channel_claim(6);
}

void RenderBuffer::clear()
{
    if (clip != bounds)
    {
        rectangle(clip);
        return;
    }

    const PixelRun clear_run { colour, (uint8_t)(bounds.w / RUNS_PER_LINE), depth };
#if 0
    PixelRun* run = static_cast<PixelRun*>(frame_buffer);
    for (int i = 0; i < bounds.h * RUNS_PER_LINE; ++i)
    {
        run[i] = clear_run;
    }
#else
    dma_channel_config c = dma_channel_get_default_config(clear_dma_channel);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    channel_config_set_read_increment(&c, false);
    channel_config_set_write_increment(&c, true);

    dma_channel_wait_for_finish_blocking(clear_dma_channel);
    dma_channel_configure(clear_dma_channel, &c, frame_buffer, &clear_run.val, bounds.h * RUNS_PER_LINE, true);
    dma_channel_wait_for_finish_blocking(clear_dma_channel);

    bufnum = 0;
#endif
}

void RenderBuffer::set_pen(uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t p = ((r & 0b11111000) >> 3) |
                 ((g & 0b11111000) << 3) |
                 ((b & 0b11111000) << 8);
    colour = p;
}

int RenderBuffer::create_pen(uint8_t r, uint8_t g, uint8_t b)
{
    uint16_t p = ((r & 0b11111000) >> 3) |
                 ((g & 0b11111000) << 3) |
                 ((b & 0b11111000) << 8);
    return p;
}

void RenderBuffer::set_pixel(const Point &p)
{
    set_pixel_span(p, 1);
}

namespace
{
    __always_inline bool run_is_same(const PixelRun& a, const PixelRun& b)
    {
        return a.colour == b.colour && a.depth == b.depth;
    }

    bool __not_in_flash("render_buffer") make_space_at(PixelRun* run, int& i)
    {
        if (i > 0 && run[i-1].run_length == 0)
        {
            --i;
        }
        else if (i > 1 && run[i-2].run_length == 0)
        {
            run[i-2] = run[i-1];
            --i;
            run[i].run_length = 0;
        }
        else if (i > 1 && run_is_same(run[i-1], run[i-2]))
        {
            run[i-2].run_length += run[i-1].run_length;
            --i;
            run[i].run_length = 0;
        }
        else if (i < RenderBuffer::RUNS_PER_LINE - 1 && run[i+1].run_length == 0)
        {
            run[i+1] = run[i];
            run[i].run_length = 0;
        }
        else if (i < RenderBuffer::RUNS_PER_LINE - 1 && run_is_same(run[i], run[i+1]))
        {
            // Can collapse current into the next run
            run[i+1].run_length += run[i].run_length;
            run[i].run_length = 0;
        }
        else
        {
            // Look for next collapsable run
            for (int dist = 2, max_dist = max(RenderBuffer::RUNS_PER_LINE - i, i - 1); dist < max_dist; ++dist)
            {
                if (i + dist < RenderBuffer::RUNS_PER_LINE)
                {
                    if (run[i + dist].run_length == 0)
                    {
                        for (int j = i + dist; j > i; --j) run[j] = run[j-1];
                        run[i].run_length = 0;
                        return true;
                    }
                    if (run_is_same(run[i + dist - 1], run[i + dist]))
                    {
                        run[i + dist].run_length += run[i + dist - 1].run_length;
                        for (int j = i + dist - 1; j > i; --j) run[j] = run[j-1];
                        run[i].run_length = 0;
                        return true;
                    }
                }
                if (i - dist > 0)
                {
                    if (run[i - dist - 1].run_length == 0)
                    {
                        --i;
                        for (int j = i - dist; j < i; ++j) run[j] = run[j+1];
                        run[i].run_length = 0;
                        return true;
                    }
                    if (run_is_same(run[i - dist - 1], run[i - dist]))
                    {
                        run[i - dist - 1].run_length += run[i - dist].run_length;
                        --i;
                        for (int j = i - dist + 1; j < i; ++j) run[j] = run[j+1];
                        run[i].run_length = 0;
                        return true;
                    }
                }
            }
            return false;
        }

        return true;
    }
}

void __not_in_flash("render_buffer") RenderBuffer::set_pixel_span(const Point& p, uint _l)
{
    int l = _l;
    if (l >= 4 * width_per_run)
    {
        // Break the run into chunks
        Point pt(p);
        while (l > 2 * width_per_run) {
            set_pixel_span(pt, 2 * width_per_run);
            l -= 2 * width_per_run;
            pt.x += 2 * width_per_run;
        }

        set_pixel_span(pt, l);
        return;
    }

    PixelRun* run = get_run(p.y, 0);
    int i;
    int x = p.x;

    // Find the correct position to insert the run
    if (x > (bounds.w >> 1)) 
    {
        x = bounds.w - x;
        for (i = RUNS_PER_LINE - 1; x - run[i].run_length >= 0 && i > 0; --i)
        {
            x -= run[i].run_length;
        }
        x = run[i].run_length - x; 
    }
    else
    {
        for (i = 0; x - run[i].run_length >= 0 && i < RUNS_PER_LINE - 1; ++i)
        {
            x -= run[i].run_length;
        }    
    }
    
    // Ignore any runs at less depth
    while (run[i].depth < depth)
    {
        l -= run[i].run_length - x;
        if (l <= 0 || ++i == RUNS_PER_LINE) {
            return;
        }
        x = 0;
    }

    if (run[i].run_length > 0 && (run[i].colour != colour || run[i].depth != depth))
    {
        // Aim now is to be pointing to the beginning of an existing run that we can overwrite
        assert(run[i].run_length > x);

        if (i == RUNS_PER_LINE - 1)
        {
            if (!make_space_at(run, i))
            {
                return;
            }
            assert(i < RUNS_PER_LINE - 1);
            run[i] = run[i+1];
            run[i+1].run_length = 0;
        }

        // Clip off the end of this run, if the new run needs to start in the middle of it
        const int remainder = run[i].run_length - x;
        run[i].run_length = x;

        ++i;
        if (l < remainder || run[i].depth < depth)
        {
            // The existing run needs to continue after the new run, try to find space for it
            if (run[i].run_length == 0)
            {
                run[i] = run[i-1];
                run[i].run_length = remainder;
            }
            else if (run_is_same(run[i-1], run[i]))
            {
                run[i].run_length += remainder;
            }
            else
            {
                PixelRun tmp = run[i-1];
                tmp.run_length = remainder;
                if (!make_space_at(run, i))
                {
                    run[i-1].run_length += remainder;
                    return;
                }
                run[i] = tmp;
            }
        }
        else
        {
            // The existing run will be covered by the new run, temporarily just add the length to the next run
            // to maintain overall length.
            run[i].run_length += remainder;
        }

        if (run[i].run_length > l)
        {
            // Existing run will continue after the new run,
            // make space for the new run
            if (!make_space_at(run, i)) return;
        }

        assert(run[i].depth >= depth || run[i].run_length == 0);

        int old_run_length = run[i].run_length;
        assert(old_run_length <= l);
        run[i].colour = colour;
        run[i].depth = depth;
        run[i].run_length = l;
        l -= old_run_length;
    }
    else
    {
        l -= run[i].run_length - x;
        if (l > 0) {
            run[i].colour = colour;
            run[i].depth = depth;
            run[i].run_length += l;
        }
    }    

    if (l > 0)
    {
        int modified_i = i;
        for (++i; i < RUNS_PER_LINE; ++i)
        {
            if (run[i].depth < depth && run[i].run_length > 0)
            {
                run[modified_i].run_length -= l;
                l -= run[i].run_length;
                if (l > 0) {
                    set_pixel_span(Point(p.x + _l - l, p.y), l);
                }
                return;
            }

            if (run[i].run_length >= l)
            {
                run[i].run_length -= l;
                return;
            }

            l -= run[i].run_length;
            run[i].run_length = 0;
        }
    }
}

void RenderBuffer::scanline_convert(PenType type, conversion_callback_func callback)
{
    if(type == PEN_RGB565) {
        const PixelRun clear_run { colour, (uint8_t)(bounds.w / RUNS_PER_LINE), depth };

        dma_channel_config c = dma_channel_get_default_config(clear_dma_channel);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        channel_config_set_read_increment(&c, false);
        channel_config_set_write_increment(&c, true);

        dma_channel_configure(clear_dma_channel, &c, frame_buffer, &clear_run.val, RUNS_PER_LINE, false);

        // Allocate two per-row temporary buffers, as the callback may transfer by DMA
        // while we're preparing the next row
        uint16_t row_buf[2][bounds.w];
        for (int y = 0; y < bounds.h; y++) {
            PixelRun* run = get_run(y, 0);

            int x = 0;
            for (int i = 0; i < RUNS_PER_LINE; i++) {
                for (int l = run[i].run_length; l > 0; --l) {
                    row_buf[y & 1][x++] = run[i].colour;
                }
            }

            // Callback to the driver with the row data
            callback(row_buf[y & 1], bounds.w * sizeof(RGB565));
            dma_channel_wait_for_finish_blocking(clear_dma_channel);
            dma_channel_start(clear_dma_channel);
        }

        dma_channel_wait_for_finish_blocking(clear_dma_channel);
    }
}

void RenderBuffer::scanvideo()
{
        const PixelRun clear_run { bg_colour, (uint8_t)(bounds.w / RUNS_PER_LINE), 255 };

        dma_channel_config c = dma_channel_get_default_config(clear_dma_channel);
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        channel_config_set_read_increment(&c, false);
        channel_config_set_write_increment(&c, true);

        dma_channel_configure(clear_dma_channel, &c, (PixelRun*)frame_buffer + (bufnum ^ 1) * bounds.h * RUNS_PER_LINE, &clear_run.val, RUNS_PER_LINE, false);

        struct scanvideo_scanline_buffer *scanline_buffer = scanvideo_begin_scanline_generation(true);
        const uint32_t frame_num = scanvideo_frame_number(scanline_buffer->scanline_id);
        while (scanvideo_frame_number(scanline_buffer->scanline_id) == frame_num) {
            uint32_t y = scanvideo_scanline_number(scanline_buffer->scanline_id);
            if (y >= DISPLAY_HEIGHT) break;

            PixelRun* run = get_run(y, 0, bufnum ^ 1);
            uint16_t* buf = (uint16_t*)scanline_buffer->data;

            int x = 0;
            uint16_t color;
            for (int i = 0; i < RUNS_PER_LINE; i++) {
                color = run[i].colour;
                uint16_t len = run[i].run_length;
                switch (len) {
                    case 0:
                        break;
                    case 1:
                        *buf++ = COMPOSABLE_RAW_1P;
                        *buf++ = color;
                        break;
                    case 2:
                        *buf++ = COMPOSABLE_RAW_2P;
                        *buf++ = color;
                        *buf++ = color;
                        break;
                    default:
                        *buf++ = COMPOSABLE_COLOR_RUN;
                        *buf++ = color;
                        *buf++ = (len - 3);
                        break;
                }
            }

            if (color != 0)
            {
                *buf++ = COMPOSABLE_RAW_1P;
                *buf++ = 0;
            }
            if (2 & (uintptr_t) buf) {
                *buf++ = COMPOSABLE_EOL_ALIGN;
            } else {
                *buf++ = COMPOSABLE_EOL_SKIP_ALIGN;
                *buf++ = 0xffff;
            }

            scanline_buffer->status = SCANLINE_OK;
            scanline_buffer->data_used = (uint32_t*)buf - scanline_buffer->data;

            scanvideo_end_scanline_generation(scanline_buffer);

            dma_channel_wait_for_finish_blocking(clear_dma_channel);
            dma_channel_start(clear_dma_channel);

            scanline_buffer = scanvideo_begin_scanline_generation(true);
        }

        scanline_buffer->status = SCANLINE_ERROR;
        scanline_buffer->data_used = 0;

        scanvideo_end_scanline_generation(scanline_buffer);

        dma_channel_wait_for_finish_blocking(clear_dma_channel);
}

PixelRun* __not_in_flash("render_buffer") RenderBuffer::get_run(int y, int x)
{
    PixelRun* run = static_cast<PixelRun*>(frame_buffer);
    return &run[y * RUNS_PER_LINE + x + bufnum * bounds.h * RUNS_PER_LINE];
}

PixelRun* __not_in_flash("render_buffer") RenderBuffer::get_run(int y, int x, int b)
{
    PixelRun* run = static_cast<PixelRun*>(frame_buffer);
    return &run[y * RUNS_PER_LINE + x + b * bounds.h * RUNS_PER_LINE];
}