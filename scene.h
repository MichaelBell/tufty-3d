#pragma once

#include <vector>
#include "sceneobject.h"

class Scene
{
public:
    void AddToScene(SceneObject* pObject);
    void RemoveFromScene(SceneObject* pObject);
    void ClearScene() { m_objects.clear(); }
    
    void RenderScene();

private:
    std::vector<SceneObject*> m_objects;
};