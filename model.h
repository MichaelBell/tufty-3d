#pragma once

#include <cstdint>
#include "vector.h"

struct Triangle
{
    uint32_t vert_idx_0 : 9;
    uint32_t vert_idx_1 : 9;
    uint32_t vert_idx_2 : 9;
    uint32_t mat_idx : 5;
    Vec3D normal;
};

struct Material
{
    Vec3D ambient_colour;
    Vec3D diffuse_colour;
};

struct Model
{
    const Vec3D* vertices;
    const Triangle* triangles;
    const Material* materials;
    uint16_t num_vertices;
    uint16_t num_triangles;
    uint8_t num_materials;
};