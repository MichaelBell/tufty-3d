#pragma once

#include "model.h"
#include "matrix.h"

Vec2D project_vertex(const Vec3D& v);
pimoroni::Point make_point(const Vec2D& v);

void fill_triangle(const Vec3D (&v)[3]);

void render_model(const Model& model);

// Render a model at a given position and orientation.  Note that scaling is not supported
void render_model(const Model& model, const Vec3D& position, const Matrix<3, 3>& orientation);
