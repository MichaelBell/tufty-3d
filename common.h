#pragma once

#include "tufty2040.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "renderbuffer.h"

extern RenderBuffer graphics;

constexpr int DISPLAY_WIDTH = pimoroni::Tufty2040::WIDTH;
constexpr int DISPLAY_HEIGHT = pimoroni::Tufty2040::HEIGHT;

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