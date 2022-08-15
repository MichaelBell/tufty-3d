#pragma once

#include "matrix.h"

struct Transform
{
    Vec3D pos = Vec3D{ 0,0,0 };
    Matrix<3, 3> orient = MAT_IDENTITY;
};

inline Transform operator*(const Transform& a, const Transform& b)
{
    Transform v;
    v.pos = a.pos + a.orient * b.pos;
    v.orient = a.orient * b.orient;
    return v;
}
