#include "lighting.h"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;

using std::min;
using std::max;

extern PicoGraphics_PenRGB565 graphics;

Vec3D light_direction = Normalize(Vec3D{ 1, 1, -1 });

RGB565 get_lit_colour(const Vec3D& normal, const Vec3D& ambient_colour, const Vec3D& diffuse_colour)
{
  const fixed_t l = Dot(light_direction, normal);

  Vec3D colour;
  if (l < fixed_t(0)) colour = ambient_colour;
  else colour = diffuse_colour * min(fixed_t(1), l) + ambient_colour;

  return __builtin_bswap16(((colour.x.val >> (FIXED_PT_PREC + 3 - 11)) & 0xf800) |
                           ((colour.y.val >> (FIXED_PT_PREC + 2 -  5)) & 0x07e0) |
                           ((colour.z.val >> (FIXED_PT_PREC + 3)) & 0x001f));
}

void set_colour_for_tri(const Triangle& tri, const Material& mat)
{
  RGB565 colour = get_lit_colour(tri.normal, mat.ambient_colour, mat.diffuse_colour);
  graphics.set_pen(colour);
}

