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
#include "button.hpp"

#include "common.h"
#include "vector.h"
#include "lighting.h"
#include "rendering.h"
#include "scene.h"
#include "teapot.h"

using namespace pimoroni;

RenderBuffer graphics(DISPLAY_WIDTH, DISPLAY_HEIGHT, nullptr);
Scene scene;

int main() {
  constexpr uint32_t CLOCK_KHZ = 250000;
  set_sys_clock_khz(CLOCK_KHZ, true);
  clock_configure(clk_peri,
                  0,
                  CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS,
                  CLOCK_KHZ * KHZ,
                  CLOCK_KHZ * KHZ);

  stdio_init_all();

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

//  sleep_ms(5000);

  graphics.set_pen(TEA_BG);
  graphics.set_depth(255);
  printf("Clearing\n");
  graphics.clear();
  printf("Start render loop\n");

  scene.Init();
  //scene.SetDisplay(&st7789);
  scene.SetBackground(TEA_BG);

#if 1
  SceneObject teapot;
  teapot.pModel = &get_teapot_model();
  teapot.transform.pos = Vec3D { 0, -2, 6 };

//  SceneObject duck;
//  duck.pModel = &get_rduck_model();
//  duck.transform.pos = Vec3D { 0, -3, 10 };

  scene.AddToScene(&teapot);

  float x = 1.2f;
  float inc = 0.01f;
  Transform camera;
  const Vec3D fwd { 0, 0, 0.5f };

  absolute_time_t start_time = get_absolute_time();
  while (true)
  {
    scene.RenderScene();

    teapot.transform.orient = mat_pitch(0.1f) * mat_yaw(x);
    //duck.transform.orient = mat_yaw(x) * mat_roll(-M_PI_2) * mat_pitch(M_PI_2);
    x += inc;
  }
#else
  Model* pOct = &get_octahedron_model();
  
  constexpr int num_particles = 20;
  SceneObject particles[num_particles];
  Vec3D vel[num_particles];
  float ang_vel[num_particles][3];

  while (true) {
  for (int i = 0; i < num_particles; ++i) {
    particles[i].pModel = pOct;
    particles[i].transform.pos = Vec3D { 0, -10, 20 };
    scene.AddToScene(&particles[i]);
    vel[i].y = fixed_t((10.f * float(random()) / RAND_MAX) + 10);
    vel[i].x = fixed_t((6.f * float(random()) / RAND_MAX) - 3);
    vel[i].z = fixed_t((6.f * float(random()) / RAND_MAX) - 3);
    ang_vel[i][0] = 4.f * (float(random()) / RAND_MAX) - 2;
    ang_vel[i][1] = 4.f * (float(random()) / RAND_MAX) - 2;
    ang_vel[i][2] = 4.f * (float(random()) / RAND_MAX) - 2;
  }

  absolute_time_t start_time = get_absolute_time();
  while (true) {
    scene.RenderScene();
    absolute_time_t end_time = get_absolute_time();
    float deltaT = absolute_time_diff_us(start_time, end_time) * 0.000001f;
    start_time = end_time;

    for (int i = 0; i < num_particles; ++i) {
      particles[i].transform.pos += vel[i] * deltaT;
      
      if (particles[i].transform.pos.y < fixed_t(-10)) {
        scene.RemoveFromScene(&particles[i]);
      }
      else {
        vel[i].y -= fixed_t(9.8f * deltaT);
        Matrix<3, 3> deltaRot = mat_yaw(ang_vel[i][1] * deltaT) * mat_roll(ang_vel[i][2] * deltaT) * mat_pitch(ang_vel[i][0] * deltaT);
        particles[i].transform.orient *= deltaRot;
      }
    }
  }  

  scene.ClearScene();
  }

#endif

  return 0;
}
