#include "pico/stdlib.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <deque>
#include <algorithm>
#include "pico/time.h"
#include "pico/platform.h"

#include "common/pimoroni_common.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "tufty2040.hpp"
#include "button.hpp"

#include "vector.h"

using namespace pimoroni;

Tufty2040 tufty;

ST7789 st7789(
  Tufty2040::WIDTH,
  Tufty2040::HEIGHT,
  ROTATE_180,
  ParallelPins{
    Tufty2040::LCD_CS,
    Tufty2040::LCD_DC,
    Tufty2040::LCD_WR,
    Tufty2040::LCD_RD,
    Tufty2040::LCD_D0, 
    Tufty2040::BACKLIGHT
  }
);

PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

Button button_a(Tufty2040::A);
Button button_b(Tufty2040::B);
Button button_c(Tufty2040::C);
Button button_up(Tufty2040::UP);
Button button_down(Tufty2040::DOWN);

const Vec2D screen_size { Tufty2040::WIDTH, Tufty2040::HEIGHT };
const Vec2D half_screen_size = screen_size >> 1;

const int screen_scale = Tufty2040::WIDTH << 5;

// Project from camera relative space (Z forward from camera, X right, Y up)
// into screen space
Vec2D project_vertex(const Vec3D& v) {
  const int inv_z = 0x40000000 / v.z.val;
  const int scale = screen_scale * inv_z;
  Vec2D rv;
  rv.x.val = scale;
  rv.y.val = -scale;
  return (Vec2D{v.x, v.y} * rv) + half_screen_size;
}

Point make_point(const Vec2D& v) {
  return Point(int(v.x), int(v.y));
}

void draw_triangle(const Vec3D (&v)[3]) {
  Point w[3];
  for (int i = 0; i < 3; ++i) {
    w[i] = make_point(project_vertex(v[i]));
    //printf("%d %d %d\t%d %d\n", v[i].x, v[i].y, v[i].z, w[i].x, w[i].y);
  }

  graphics.line(w[0], w[1]);
  graphics.line(w[1], w[2]);
  graphics.line(w[2], w[0]);
}

void draw_cube(float theta, float phi) {
  Vec3D cube[8] = {
    { 1, 1, 1 },
    { -1, 1, 1 },
    { -1, -1, 1 },
    { 1, -1, 1 },
    { 1, 1, -1 },
    { -1, 1, -1 },
    { -1, -1, -1 },
    { 1, -1, -1 }
  };

  Vec3D offset { 0, 0, 4};
  Point w[8];
  for (int i = 0; i < 8; ++i) {
    Vec3D v;
    fixed_t cp(cosf(phi));
    fixed_t sp(sinf(phi));
    v.x = cube[i].x;
    v.y = cube[i].y * cp + cube[i].z * sp;
    v.z = cube[i].z * cp - cube[i].y * sp;
    cube[i] = v;

    fixed_t ct(cosf(theta));
    fixed_t st(sinf(theta));
    v.x = cube[i].x * ct + cube[i].y * st;
    v.y = cube[i].y * ct - cube[i].x * st;
    v.z = cube[i].z;

    v += offset;

    w[i] = make_point(project_vertex(v));
  }

  for (int i = 0; i < 4; ++i) {
    graphics.line(w[i], w[(i+1)&3]);
    graphics.line(w[i + 4], w[((i+1)&3) + 4]);
    graphics.line(w[i], w[i+4]);
  }
}

int main() {
  stdio_init_all();

  st7789.set_backlight(255);

  Pen WHITE = graphics.create_pen(255, 255, 255);
  Pen BG = graphics.create_pen(120, 40, 60);

  uint8_t i = 0;

  graphics.set_pen(BG);
  graphics.clear();
  st7789.update(&graphics);

  Vec3D tri[3] = {
    { -1, 0, 4 },
    { 0, -1, 4 },
    { 0, 0, 4 }
  };

#if 1
  float phi = 0;
  float theta = 0;
  while (true) {
    phi += 0.01f;
    theta += 0.002f;

    graphics.set_pen(BG);
    graphics.clear();
    graphics.set_pen(WHITE);
    draw_cube(theta, phi);
    st7789.update(&graphics);
  }
#endif
  for (fixed_t i = 1; int(i) < 16; i += fixed_t(0, 1 << 10)) {
    graphics.set_pen(BG);
    graphics.clear();
    graphics.set_pen(WHITE);
    for (int j = 0; j < 3; ++j) {
      tri[j].z = i;
    }
    draw_triangle(tri);
    st7789.update(&graphics);
  }

  return 0;
}
