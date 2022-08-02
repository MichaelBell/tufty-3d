#include "common.h"
#include "model.h"
#include "lighting.h"

void set_triangle_normals(Model& model)
{
    for (uint16_t i = 0; i < model.num_triangles; ++i)
    {
        Triangle& tri = model.triangles[i];
        const Vec3D& v0 = model.vertices[tri.vert_idx[0]];
        const Vec3D perp = Cross((model.vertices[tri.vert_idx[1]] - v0), (model.vertices[tri.vert_idx[2]] - v0));
        tri.normal = Normalize(perp);
    }
}