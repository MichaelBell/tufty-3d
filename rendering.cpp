#include "common.h"
#include "rendering.h"
#include "lighting.h"

using namespace pimoroni;

const Vec2D screen_size { Tufty2040::WIDTH, Tufty2040::HEIGHT };
const Vec2D half_screen_size = screen_size >> 1;

const int screen_scale = Tufty2040::WIDTH << 5;

// Project from camera relative space (Z forward from camera, X right, Y up)
// into screen space
Vec2D project_vertex(const Vec3D& v) {
  const int inv_z = 0x40000000 / v.z.val;
  const int scale = screen_scale * inv_z;
  Vec2D rv;
  rv.x.val = scale;
  rv.y.val = -scale;
  return (Vec2D{v.x, v.y} * rv) + half_screen_size;
}

Point make_point(const Vec2D& v) {
  return Point(int(v.x), int(v.y));
}

bool is_back_face(const Vec2D (&w)[3]) {
  Vec2D a = w[2] - w[0];
  Vec2D b = w[1] - w[0];
  return (a.x * b.y >= a.y * b.x);
}

void set_depth_for_triangle(const Vec3D (&v)[3]) {
  fixed_t z = v[0].z + v[1].z + v[2].z;
  int d = z.val >> (FIXED_PT_PREC - 5);
  if (d > 254 * 254) d = 254;
  else if (d > 3) d = isqrt(d);
  else d = 1;

  graphics.set_depth(d);
}

void fill_triangle(const Vec3D (&v)[3]) {
  Vec2D w[3];
  for (int i = 0; i < 3; ++i) {
    w[i] = project_vertex(v[i]);
  }

  if (is_back_face(w)) return;

  set_depth_for_triangle(v);

  // Order points so first has least y coord, and second has lower x coord than third
  struct RasterPoint
  {
    fixed_t x;
    int y;
    RasterPoint() = default;
    RasterPoint(const Vec2D& v)
      : x(v.x)
      , y(v.y)
    {}
  } wo[3];
  if (w[0].y < w[1].y && w[0].y < w[2].y) {
    wo[0] = w[0];
    if (w[1].x < w[2].x) {
      wo[1] = w[1];
      wo[2] = w[2];
    } else {
      wo[1] = w[2];
      wo[2] = w[1];
    }
  } else if (w[1].y < w[0].y && w[1].y < w[2].y) {
    wo[0] = w[1];
    if (w[0].x < w[2].x) {
      wo[1] = w[0];
      wo[2] = w[2];
    } else {
      wo[1] = w[2];
      wo[2] = w[0];
    }
  }
  else {
    wo[0] = w[2];
    if (w[0].x < w[1].x) {
      wo[1] = w[0];
      wo[2] = w[1];
    } else {
      wo[1] = w[1];
      wo[2] = w[0];
    }
  }

  if (wo[0].y >= Tufty2040::HEIGHT) return;
  const int end_y = min(max(wo[1].y, wo[2].y), Tufty2040::HEIGHT - 1);
  if (end_y < 0) return;

  const int min_x = max(0, int(min(wo[0].x, wo[1].x)));
  const int max_x = min(Tufty2040::WIDTH - 1, int(max(wo[0].x, wo[2].x)));

  if (wo[0].y == end_y) {
    graphics.pixel_span(Point(min_x, wo[0].y), max_x - min_x + 1);
    return;
  }

  fixed_t start_x = wo[0].x;
  fixed_t end_x = wo[0].x;
  fixed_t grad_start_x;
  fixed_t grad_end_x;
  if (wo[1].y > wo[0].y) {
    grad_start_x = (wo[1].x - wo[0].x) / (wo[1].y - wo[0].y);
  } else {
    grad_start_x = wo[1].x - wo[0].x;
  }

  if (wo[2].y > wo[0].y) {
    grad_end_x = (wo[2].x - wo[0].x) / (wo[2].y - wo[0].y);
  } else {
    grad_end_x = wo[2].x - wo[0].x;
  }
  if (grad_start_x > grad_end_x)
  {
    std::swap(grad_start_x, grad_end_x);
    std::swap(wo[1], wo[2]);
  }

  bool new_start = true;
  bool new_end = true;
  for (int y = wo[0].y; y <= end_y; ++y) {
    if (y != end_y && wo[1].y == y) {
      start_x = wo[1].x;
      if (wo[2].y > y) {
        grad_start_x = (wo[2].x - start_x) / (wo[2].y - y);
        new_start = true;
      }
    }
    else {
      if (new_start) {
        start_x += grad_start_x >> 1;
        new_start = false;
      } else {
        start_x += grad_start_x;
      }
    }
    if (y != end_y && wo[2].y == y) {
      end_x = wo[2].x;
      if (wo[1].y > y) {
        grad_end_x = (wo[1].x - end_x) / (wo[1].y - y);
        new_end = true;
      }
    }
    else {
      if (new_end) {
        end_x += grad_end_x >> 1;
        new_end = false;
      } else {
        end_x += grad_end_x;
      }
    }

    if (y >= 0) {
      const int clamped_start_x = max(int(start_x), min_x);
      const int clamped_end_x = min(int(end_x), max_x);
      const int clamped_len(clamped_end_x - clamped_start_x + 1);
      if (clamped_len > 0) {
        graphics.pixel_span(Point(int(clamped_start_x), y), clamped_len);
      }
    }
  }
}

void render_model(const Model& model)
{
    for (uint16_t i = 0; i < model.num_triangles; ++i)
    {
        Vec3D v[3];
        Triangle& tri = model.triangles[i];
        set_colour_for_normal(tri.normal, model.materials[tri.mat_idx]);

        v[0] = model.vertices[tri.vert_idx[0]];
        v[1] = model.vertices[tri.vert_idx[1]];
        v[2] = model.vertices[tri.vert_idx[2]];
        fill_triangle(v);
    }
}

void render_model(const Model& model, const Vec3D& position, const Matrix<3, 3>& orientation)
{
    for (uint16_t i = 0; i < model.num_triangles; ++i)
    {
        Triangle& tri = model.triangles[i];
        Vec3D normal = orientation * tri.normal;
        set_colour_for_normal(normal, model.materials[tri.mat_idx]);

        Vec3D v[3];
        v[0] = orientation * model.vertices[tri.vert_idx[0]] + position;
        v[1] = orientation * model.vertices[tri.vert_idx[1]] + position;
        v[2] = orientation * model.vertices[tri.vert_idx[2]] + position;
        fill_triangle(v);
    }
}