#include "scene.h"
#include "common.h"
#include "rendering.h"

#include <algorithm>

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
    
void Scene::RenderScene()
{
    for (const auto* pObject : m_objects)
    {
        render_object(*pObject);
    }
}