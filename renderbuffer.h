#pragma once

struct PixelRun
{
    pimoroni::RGB565 colour;
    uint8_t run_length;
    uint8_t depth;
};

struct RenderBuffer : public pimoroni::PicoGraphics
{
    pimoroni::RGB565 colour;
    uint8_t depth;

    static constexpr int RUNS_PER_LINE = 64;
    const uint8_t width_per_run;

    RenderBuffer(uint16_t width, uint16_t height, void *frame_buffer);

    void clear();
    void set_depth(uint8_t d) { depth = d; }
    void set_pen(uint c) override { colour = c; }
    void set_pen(uint8_t r, uint8_t g, uint8_t b) override;
    int create_pen(uint8_t r, uint8_t g, uint8_t b) override;
    void set_pixel(const pimoroni::Point &p) override;
    void set_pixel_span(const pimoroni::Point &p, uint l) override;
    void scanline_convert(PenType type, conversion_callback_func callback) override;

    static size_t buffer_size(uint w, uint h) {
        return h * RUNS_PER_LINE * sizeof(PixelRun);
    }

private:
    PixelRun* get_run(int y, int x);
};