#pragma once

#include "libraries/pico_graphics/pico_graphics.hpp"
#include "renderbuffer.h"

extern RenderBuffer graphics;

constexpr int DISPLAY_WIDTH = 640;
constexpr int DISPLAY_HEIGHT = 240;

using std::min, std::max;

namespace pimoroni
{
    inline bool operator==(const Rect& a, const Rect& b)
    {
        return a.x == b.x && a.y == b.y && a.w == b.w && a.h == b.y;
    }

    inline bool operator!=(const Rect& a, const Rect& b)
    {
        return a.x != b.x || a.y != b.y || a.w != b.w || a.h != b.h;
    }
}