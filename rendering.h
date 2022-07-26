#pragma once

#include "model.h"

Vec2D project_vertex(const Vec3D& v);
pimoroni::Point make_point(const Vec2D& v);

void fill_triangle(const Vec3D* vertices, const Triangle& tri);

void render_model(const Model& model);