#include "common.h"
#include "model.h"
#include "lighting.h"

void set_triangle_normals(Model& model)
{
    for (uint16_t i = 0; i < model.num_triangles; ++i)
    {
        Triangle& tri = model.triangles[i];
        const Vec3D& v0 = model.vertices[tri.vert_idx_0];
        const Vec3D perp = Cross((model.vertices[tri.vert_idx_1] - v0), (model.vertices[tri.vert_idx_2] - v0));
        tri.normal = Normalize(perp);
    }
}