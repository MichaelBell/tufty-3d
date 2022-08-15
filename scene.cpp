#include "scene.h"
#include "common.h"
#include "rendering.h"

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

void Scene::RenderScene()
{
    absolute_time_t render_start_time = get_absolute_time();
    for (const auto* pObject : m_objects)
    {
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
        graphics.text(buf, Point(230, 6), Tufty2040::WIDTH);
    }

    graphics.set_pen(m_bgPen);
    graphics.set_depth(255);
    m_st7789->update(&graphics);
}