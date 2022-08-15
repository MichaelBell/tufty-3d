#pragma once

#include "transform.h"
#include "model.h"

// A model at a position
struct SceneObject
{
    Transform transform;
    Model* pModel = nullptr;
};
