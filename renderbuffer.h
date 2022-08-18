#pragma once

union PixelRun
{
    struct {
        pimoroni::RGB565 colour;
        uint8_t run_length;
        uint8_t depth;
    };
    uint32_t val;

    PixelRun() = default;
    PixelRun(pimoroni::RGB565 c, uint8_t rl, uint8_t d)
      : colour(c), run_length(rl), depth(d) {}
    PixelRun(const PixelRun& other) : val(other.val) {}
    PixelRun& operator=(const PixelRun& other) { val = other.val; return *this; }
};

struct RenderBuffer : public pimoroni::PicoGraphics
{
    pimoroni::RGB565 colour;
    pimoroni::RGB565 bg_colour;
    uint8_t depth;
    uint8_t bufnum = 0;

    static constexpr int RUNS_PER_LINE = 64;
    const uint8_t width_per_run;

    uint clear_dma_channel;

    RenderBuffer(uint16_t width, uint16_t height, void *frame_buffer);

    void clear();
    void set_depth(uint8_t d) { depth = d; }
    void set_pen(uint c) override { colour = c; }
    void set_bg_pen(uint c) { bg_colour = c; }
    void set_pen(uint8_t r, uint8_t g, uint8_t b) override;
    int create_pen(uint8_t r, uint8_t g, uint8_t b) override;
    void set_pixel(const pimoroni::Point &p) override;
    void set_pixel_span(const pimoroni::Point &p, uint l) override;
    void scanline_convert(PenType type, conversion_callback_func callback) override;
    
    void switch_buffer() { bufnum ^= 1; }
    void scanvideo();

private:
    PixelRun* get_run(int y, int x);
    PixelRun* get_run(int y, int x, int b);
};