#include "common.h"
#include "renderbuffer.h"

using namespace pimoroni;

RenderBuffer::RenderBuffer(uint16_t width, uint16_t height, void *frame_buffer)
    : PicoGraphics(width, height, frame_buffer)
    , width_per_run(width / RUNS_PER_LINE)
{
    assert((width % RUNS_PER_LINE) == 0);
    assert(4 * width_per_run < 256);

    pen_type = PEN_1BIT;  // Anything that gets scanline convert called on it.
    if (this->frame_buffer == nullptr) {
        this->frame_buffer = (void *)(new uint8_t[buffer_size(width, height)]);
    }
}

void RenderBuffer::clear()
{
    if (clip != bounds)
    {
        rectangle(clip);
        return;
    }

    PixelRun* run = static_cast<PixelRun*>(frame_buffer);
    PixelRun clear_run { colour, (uint8_t)(bounds.w / RUNS_PER_LINE), depth };
    for (int i = 0; i < bounds.h * RUNS_PER_LINE; ++i)
    {
        run[i] = clear_run;
    }
}

void RenderBuffer::set_pen(uint8_t r, uint8_t g, uint8_t b)
{
    colour = RGB(r, g, b).to_rgb565();
}

int RenderBuffer::create_pen(uint8_t r, uint8_t g, uint8_t b)
{
    return RGB(r, g, b).to_rgb565();
}

void RenderBuffer::set_pixel(const Point &p)
{
    set_pixel_span(p, 1);
}

bool run_is_same(const PixelRun& a, const PixelRun& b)
{
    return a.colour == b.colour && a.depth == b.depth;
}

void RenderBuffer::set_pixel_span(const Point& p, uint _l)
{
    int l = _l;
    if (l > 4 * width_per_run)
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
    int last_same = -1;
    int last_zero = -1;

    // Find the correct position to insert the run
    for (i = 0; x - run[i].run_length >= 0 && i < RUNS_PER_LINE - 1; ++i)
    {
        if (run[i].run_length == 0)
        {
            last_zero = i;
        }
        else if (run[i+1].run_length > 0 && run_is_same(run[i], run[i+1]))
        {
            last_same = i;
        }

        x -= run[i].run_length;
    }

    while (run[i].depth < depth && l > 0)
    {
        l -= run[i].run_length - x;
        x = 0;
        if (++i == RUNS_PER_LINE) {
            return;
        }
    }

    if (l <= 0)
    {
        return;
    }

    while (run[i].run_length == 0 && i < RUNS_PER_LINE - 1)
    {
        ++i;
    }

    if (run[i].run_length > x)
    {
        const int remainder = run[i].run_length - x;
        run[i].run_length = x;

        if (i < RUNS_PER_LINE - 1)
        {
            if (l < remainder)
            {
                if (run[i+1].run_length == 0)
                {
                    run[i+1] = run[i];
                    run[i+1].run_length = remainder;
                }
                else if (run_is_same(run[i], run[i+1]))
                {
                    run[i+1].run_length += remainder;
                }
                else
                {
                    // TODO Need to collapse a run to add in a new run for the second half of the old run
                    return;
                }
            }
            else
            {
                ++i;
                run[i].run_length += remainder;
            }
        }
        else
        {
            // TODO Need to collapse a previous run to sort this out
            return;
        }
    }
    else
    {
        assert(i == RUNS_PER_LINE - 1);
        if (run[i].run_length > 0)
        {
            if (last_zero == i-1)
            {
                run[i-1] = run[i];
                run[i].run_length = 0;
            }
            else if (last_same == i-1)
            {
                run[i-1].run_length += run[i].run_length;
                run[i].run_length = 0;
            }
            else
            {
                // TODO
                return;
            }
        }
    }

    if (run[i].run_length > l)
    {
        // Make space for the new run
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
        else if (i < RUNS_PER_LINE - 1 && run[i+1].run_length == 0)
        {
            run[i+1] = run[i];
            run[i].run_length = 0;
        }
        else if (i < RUNS_PER_LINE - 1 && run_is_same(run[i], run[i+1]))
        {
            // Can collapse current into the next run
            run[i+1].run_length += run[i].run_length;
            run[i].run_length = 0;
        }
        else
        {
            // Look for next collapsable run
            // TODO
            return;
#if 0
            const int dist_to_last = (last_same != -1) ? i - last_same : RUNS_PER_LINE;
            const int cutoff = min(RUNS_PER_LINE - 2, i + dist_to_last);
            int next_same;
            for (next_same = i+1; next_same < RUNS_PER_LINE - 2; ++next_same)
            {
                if (run_is_same(run[next_same], run[next_same+1]))
                {
                    break;
                }
            }

            if (next_same < cutoff)
            {
                // Can collapse at next_same and then move entries between up
            }
#endif
        }
    }

    int old_run_length = run[i].run_length;
    assert(old_run_length <= l);
    run[i].colour = colour;
    run[i].depth = depth;
    run[i].run_length = l;
    l -= old_run_length;

    if (l > 0)
    {
        for (++i; i < RUNS_PER_LINE; ++i)
        {
            if (run[i].run_length >= l)
            {
                run[i].run_length -= l;
                break;
            }

            l -= run[i].run_length;
            run[i].run_length = 0;
        }
    }
}

void RenderBuffer::scanline_convert(PenType type, conversion_callback_func callback)
{
    if(type == PEN_RGB565) {
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
        }
    }
}

PixelRun* RenderBuffer::get_run(int y, int x)
{
    PixelRun* run = static_cast<PixelRun*>(frame_buffer);
    return &run[y * RUNS_PER_LINE + x];
}