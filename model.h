#pragma once

#include <cstdint>
#include "vector.h"

struct Triangle
{
    uint8_t vert_idx[3];
    uint8_t mat_idx;
    Vec3D normal;
};

struct Material
{
    Vec3D ambient_colour;
    Vec3D diffuse_colour;
};

struct Model
{
    Vec3D* vertices;
    Triangle* triangles;
    Material* materials;
    uint8_t num_vertices;
    uint8_t num_materials;
    uint16_t num_triangles;
};

void set_triangle_normals(Model& model);