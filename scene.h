#pragma once

#include <vector>
#include "sceneobject.h"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "drivers/st7789/st7789.hpp"

class Scene
{
public:
    void Init();

    void SetDisplay(pimoroni::ST7789* st7789) { m_st7789 = st7789; }

    void AddToScene(SceneObject* pObject);
    void RemoveFromScene(SceneObject* pObject);
    void ClearScene() { m_objects.clear(); }
    
    void SetBackground(pimoroni::Pen bgPen) { m_bgPen = bgPen; }
    void ShowFps(bool enable) { m_fps = enable; }
    void ToggleFps() { m_fps = !m_fps; }

    void SetCameraTransform(const Transform& camera);

    void RenderScene();

private:
    friend void core_1_init();
    void Core1Loop();

    pimoroni::ST7789* m_st7789 = nullptr;
    pimoroni::Pen m_bgPen = 0;
    bool m_fps = true;
    absolute_time_t m_lastFrameTime;

    Transform m_inverseCamera;
    std::vector<SceneObject*> m_objects;

    struct RenderCommand
    {
        Model* pModel;
        Transform transform;
    };
    std::vector<RenderCommand> m_renderCmds;
};