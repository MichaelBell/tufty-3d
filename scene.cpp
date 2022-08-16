#include "scene.h"
#include "common.h"
#include "rendering.h"
#include "pico/multicore.h"

#include <algorithm>

using namespace pimoroni;

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
      for (int j = 0; i < 3; ++j) {
        m_inverseCamera.orient(i, j) = camera.orient(j, i);
      }
    }
}

void core_1_init()
{
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

    for (const auto& cmd : m_renderCmds)
    {
        render_model(*cmd.pModel, cmd.transform.pos, cmd.transform.orient);
    }

    absolute_time_t end_time = get_absolute_time();
    int64_t frame_time_us = absolute_time_diff_us(m_lastFrameTime, end_time);
    m_lastFrameTime = end_time;

    if (m_fps) {
        char buf[20];
        sprintf(buf, "FPS: %.1f", 1000000.f / frame_time_us);
        printf("%s\n", buf);
        graphics.set_pen(0xffff);
        graphics.set_depth(0);
        graphics.text(buf, Point(230, 6), Tufty2040::WIDTH);
    }

    graphics.set_pen(m_bgPen);
    graphics.set_depth(255);
    m_st7789->update(&graphics);

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
    // Wait for previous frame to finish writing out to display
    multicore_fifo_pop_blocking();

    // Render objects
    absolute_time_t render_start_time = get_absolute_time();
    m_renderCmds.resize(m_objects.size());
    for (size_t i = 0, iEnd = m_objects.size(); i < iEnd; ++i)
    {
        const auto* pObject = m_objects[i];
        RenderCommand& cmd = m_renderCmds[i];
        cmd.pModel = pObject->pModel;
        cmd.transform = m_inverseCamera * pObject->transform;
    }
    printf("Render time: %lldus\n", absolute_time_diff_us(render_start_time, get_absolute_time()));

    // Write renderbuffer to display
    multicore_fifo_push_blocking(0);
}