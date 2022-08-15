#include "pico/stdlib.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <deque>
#include <algorithm>
#include "pico/time.h"
#include "pico/platform.h"
#include "hardware/clocks.h"

#include "common/pimoroni_common.hpp"
#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "tufty2040.hpp"
#include "button.hpp"

#include "common.h"
#include "vector.h"
#include "lighting.h"
#include "rendering.h"
#include "scene.h"
#include "teapot.h"

using namespace pimoroni;

RenderBuffer graphics(Tufty2040::WIDTH, Tufty2040::HEIGHT, nullptr);
Scene scene;

int main() {
  constexpr uint32_t CLOCK_KHZ = 192000;
  set_sys_clock_khz(CLOCK_KHZ, true);
  clock_configure(clk_peri,
                  0,
                  CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                  CLOCK_KHZ * KHZ,
                  CLOCK_KHZ * KHZ);

  stdio_init_all();

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

  Button button_a(Tufty2040::A, Polarity::ACTIVE_HIGH);
  Button button_b(Tufty2040::B, Polarity::ACTIVE_HIGH);
  Button button_c(Tufty2040::C, Polarity::ACTIVE_HIGH);
  Button button_up(Tufty2040::UP, Polarity::ACTIVE_HIGH);
  Button button_down(Tufty2040::DOWN, Polarity::ACTIVE_HIGH);

  //sleep_ms(5000);

  st7789.set_backlight(255);

  Pen WHITE = graphics.create_pen(255, 255, 255);
  Pen RED = graphics.create_pen(255, 0, 0);
  Pen GREEN = graphics.create_pen(0, 255, 0);
  Pen BLUE = graphics.create_pen(0, 0, 255);
  Pen DUCK_BG = graphics.create_pen(40, 60, 120);
  Pen TEA_BG = graphics.create_pen(120, 20, 40);
  bool show_duck = false;

  Material mat_white = make_material_for_colour(RGB(255, 255, 255));
  Material mat_red = make_material_for_colour(RGB(255, 0, 0));
  Material mat_green = make_material_for_colour(RGB(0, 255, 0));
  Material mat_blue = make_material_for_colour(RGB(0, 0, 255));

  uint8_t i = 0;

  graphics.set_pen(TEA_BG);
  graphics.set_depth(255);
  printf("Clearing\n");
  graphics.clear();
  printf("Update display\n");
  st7789.update(&graphics);
  printf("Start render loop\n");

  SceneObject duck;
  duck.pModel = &get_rduck_model();
  duck.transform.pos = Vec3D { 0, -3, 10 };

  SceneObject teapot;
  teapot.pModel = &get_teapot_model();
  teapot.transform.pos = Vec3D { 0, -2, 6 };

  SceneObject squirrel;
  squirrel.pModel = &get_squirrel_model();
  squirrel.transform.pos = Vec3D { 0, -18, 38 };

  scene.Init();
  scene.SetDisplay(&st7789);
  scene.SetBackground(TEA_BG);
  scene.AddToScene(&squirrel);

  float x = 1.2f;
  float inc = 0.00f;

  absolute_time_t start_time = get_absolute_time();
  while (true)
  {
    scene.RenderScene();

    if (button_down.raw()) inc = 0.f;
    if (button_up.raw()) inc = 0.01f;
    if (button_a.raw()) {
      scene.SetBackground(TEA_BG);
      scene.ClearScene();
      scene.AddToScene(&squirrel);
    }
    if (button_b.read()) scene.ToggleFps();
    if (button_c.raw()) {
      scene.SetBackground(DUCK_BG);
      scene.ClearScene();
      scene.AddToScene(&duck);
    }

    teapot.transform.orient = mat_yaw(x);
    duck.transform.orient = mat_yaw(x) * mat_roll(-M_PI_2) * mat_pitch(M_PI_2);
    squirrel.transform.orient = mat_yaw(x) * mat_roll(-M_PI_2) * mat_pitch(M_PI_2);
    x += inc;
  }

  return 0;
}
