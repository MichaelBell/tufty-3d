#include "common.h"
#include "model.h"
#include "lighting.h"

namespace {

constexpr __in_flash("model") Vec3D octahedron_vertices[] = {
  { -0.000000f, 0.000000f, 1.000000f },
  { -0.000000f, 1.000000f, 0.000000f },
  { -1.000000f, 0.000000f, 0.000000f },
  { -0.000000f, 0.000000f, -1.000000f },
  { -0.000000f, -1.000000f, 0.000000f },
  { 1.000000f, 0.000000f, 0.000000f },
};

constexpr __in_flash("model") Triangle octahedron_tris[] = {
  { 0, 1, 2, 0, { -0.577350f, 0.577350f, 0.577350f } },
  { 0, 2, 4, 0, { -0.577350f, -0.577350f, 0.577350f } },
  { 0, 4, 5, 0, { 0.577350f, -0.577350f, 0.577350f } },
  { 0, 5, 1, 0, { 0.577350f, 0.577350f, 0.577350f } },
  { 3, 1, 5, 0, { 0.577350f, 0.577350f, -0.577350f } },
  { 3, 5, 4, 0, { 0.577350f, -0.577350f, -0.577350f } },
  { 3, 4, 2, 0, { -0.577350f, -0.577350f, -0.577350f } },
  { 3, 2, 1, 0, { -0.577350f, 0.577350f, -0.577350f } },
};
constexpr __in_flash("model") Material octahedron_mats[] = {
  { { 28.235280f, 28.235280f, 28.235280f }, { 151.764630f, 210.784280f, 16.862665f } },
};

Model octahedron_model {
  octahedron_vertices,
  octahedron_tris,
  octahedron_mats,
  sizeof(octahedron_vertices) / sizeof(octahedron_vertices[0]),
  sizeof(octahedron_tris) / sizeof(octahedron_tris[0]),
  sizeof(octahedron_mats) / sizeof(octahedron_mats[0])
};
}

Model& get_octahedron_model() {
  return octahedron_model;
}

