#include "scene.h"
#include "common.h"
#include "rendering.h"
#include "pico/multicore.h"
#include "pico/scanvideo.h"

#include <algorithm>

using namespace pimoroni;

const scanvideo_mode_t vga_mode =
        {
                .default_timing = &vga_timing_640x480_60_default,
                .pio_program = &video_24mhz_composable,
                .width = 640,
                .height = 240,
                .xscale = 1,
                .yscale = 2,
        };


void Scene::AddToScene(SceneObject* pObject)
{
    m_objects.push_back(pObject);
}

void Scene::RemoveFromScene(SceneObject* pObject)
{
    auto it = std::find(m_objects.begin(), m_objects.end(), pObject);
    if (it != m_objects.end()) 
    {
        std::iter_swap(it, m_objects.end() - 1);
        m_objects.pop_back();
    }
}

void Scene::SetCameraTransform(const Transform& camera)
{
    m_inverseCamera.pos = -camera.pos;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        m_inverseCamera.orient(i, j) = camera.orient(j, i);
      }
    }
}

void core_1_init()
{
  scanvideo_setup(&vga_mode);
  scanvideo_timing_enable(true);

  printf("Video timing enabled\n");

  Scene* pScene = (Scene*)multicore_fifo_pop_blocking();
  pScene->Core1Loop();
}

void Scene::Core1Loop()
{
  printf("Core 1 start\n");

  multicore_fifo_push_blocking(0);

  while (true)
  {
    // Wait for render buffer to be written
    multicore_fifo_pop_blocking();

    graphics.set_bg_pen(m_bgPen);
    graphics.scanvideo();

    // Indicate we are done with the render buffer
    multicore_fifo_push_blocking(0);
  }
}

void Scene::Init()
{
    multicore_launch_core1(core_1_init);
    multicore_fifo_push_blocking((int)this);
}

void Scene::RenderScene()
{
    // Render objects
    absolute_time_t render_start_time = get_absolute_time();
    for (size_t i = 0, iEnd = m_objects.size(); i < iEnd; ++i)
    {
        const auto* pObject = m_objects[i];
        Transform t = m_inverseCamera * pObject->transform;
        render_model(*pObject->pModel, t.pos, t.orient);
    }
    printf("Render time: %lldus\n", absolute_time_diff_us(render_start_time, get_absolute_time()));

    absolute_time_t end_time = get_absolute_time();
    int64_t frame_time_us = absolute_time_diff_us(m_lastFrameTime, end_time);
    m_lastFrameTime = end_time;

    if (m_fps) {
        char buf[20];
        sprintf(buf, "FPS: %.1f", 1000000.f / frame_time_us);
        printf("%s\n", buf);
        graphics.set_pen(0xffff);
        graphics.set_depth(0);
        graphics.text(buf, Point(DISPLAY_WIDTH - 90, 6), DISPLAY_WIDTH);
    }

    // Wait for previous frame to finish writing out to display
    multicore_fifo_pop_blocking();

    // Switch buffers
    graphics.switch_buffer();

    // Write renderbuffer to display
    multicore_fifo_push_blocking(0);
}