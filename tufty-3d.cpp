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

#include "common.h"
#include "vector.h"
#include "lighting.h"
#include "rendering.h"
#include "teapot.h"

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

RenderBuffer graphics(st7789.width, st7789.height, nullptr);

Button button_a(Tufty2040::A);
Button button_b(Tufty2040::B);
Button button_c(Tufty2040::C);
Button button_up(Tufty2040::UP);
Button button_down(Tufty2040::DOWN);

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

  //sleep_ms(5000);

  st7789.set_backlight(255);

  Pen WHITE = graphics.create_pen(255, 255, 255);
  Pen RED = graphics.create_pen(255, 0, 0);
  Pen GREEN = graphics.create_pen(0, 255, 0);
  Pen BLUE = graphics.create_pen(0, 0, 255);
  Pen BG = graphics.create_pen(120, 40, 60);

  Material mat_white = make_material_for_colour(RGB(255, 255, 255));
  Material mat_red = make_material_for_colour(RGB(255, 0, 0));
  Material mat_green = make_material_for_colour(RGB(0, 255, 0));
  Material mat_blue = make_material_for_colour(RGB(0, 0, 255));

  uint8_t i = 0;

  graphics.set_pen(BG);
  graphics.set_depth(255);
  printf("Clearing\n");
  graphics.clear();
  printf("Update display\n");
  st7789.update(&graphics);
  printf("Start render loop\n");

#if 0
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
#if 0
  for (float phi = 0; phi < 7.f; phi += 0.01f) {
    graphics.set_pen(BG);
    graphics.clear();

    Model tri_model;
    Vec3D tri[] = {
      { 0, 0, 4 },
      { 0, 0, 4 },
      { 0, 0, 3 }
    };
    tri_model.vertices = tri;
    tri_model.num_vertices = 3;
    Triangle triangles[] = { { { 0, 1, 2 }, 0 } };
    tri_model.triangles = triangles;
    tri_model.num_triangles = 1;
    tri_model.materials = &mat_white;
    tri_model.num_materials = 1;

    tri[0].x = cosf(phi);
    tri[0].y = sinf(phi);
    tri[1].x = cosf(phi + 1.1f);
    tri[1].y = sinf(phi + 1.1f);
    set_triangle_normals(tri_model);
    render_model(tri_model);

    tri[0] = tri[1];
    tri[1].x = cosf(phi + 2.2f);
    tri[1].y = sinf(phi + 2.2f);
    tri_model.materials = &mat_red;
    set_triangle_normals(tri_model);
    render_model(tri_model);

    tri[0] = tri[1];
    tri[1].x = cosf(phi + 3.3f);
    tri[1].y = sinf(phi + 3.3f);
    tri_model.materials = &mat_green;
    set_triangle_normals(tri_model);
    render_model(tri_model);

    tri[0] = tri[1];
    tri[1].x = cosf(phi + 4.4f);
    tri[1].y = sinf(phi + 4.4f);
    tri_model.materials = &mat_blue;
    set_triangle_normals(tri_model);
    render_model(tri_model);

    st7789.update(&graphics);

    if (phi > 2 * M_PI) phi -= 2 * M_PI;
  }
#endif

#if 0
  Model& teapot_model = get_rduck_model();
  Matrix<3, 3> orient = mat_roll(-M_PI_2) * mat_pitch(M_PI_2);
#else
  Model& teapot_model = get_teapot_model();
  Matrix<3, 3> orient = MAT_IDENTITY;
#endif
  float x = 0;

  absolute_time_t start_time = get_absolute_time();
  while (true)
  {
    graphics.set_pen(BG);
    graphics.set_depth(255);
    graphics.clear();

    //render_model(teapot_model, Vec3D { 0, -3, 10 }, orient);
    render_model(teapot_model, Vec3D { 0, 0, 6 }, orient);

    absolute_time_t end_time = get_absolute_time();
    int64_t frame_time_us = absolute_time_diff_us(start_time, end_time);
    start_time = end_time;

    char buf[20];
    sprintf(buf, "FPS: %d", 1000000 / frame_time_us);
    printf("%s\n", buf);
    graphics.set_pen(WHITE);
    graphics.set_depth(0);
    graphics.text(buf, Point(240, 6), Tufty2040::WIDTH);

    st7789.update(&graphics);
    //orient = /*mat_roll(x * 0.25f) * */ mat_yaw(x) * mat_roll(-M_PI_2) * mat_pitch(M_PI_2);
    orient = mat_yaw(x);
    x += 0.02f;
  }

  return 0;
}
