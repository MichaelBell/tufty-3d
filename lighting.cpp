#include "common.h"
#include "lighting.h"

using namespace pimoroni;

Vec3D light_direction = Normalize(Vec3D{ 1, 1, -1 });

RGB565 __not_in_flash("rendering") get_lit_colour(const Vec3D& normal, const Vec3D& ambient_colour, const Vec3D& diffuse_colour)
{
  const fixed_t l = DotNormals(light_direction, normal);

  Vec3D colour;
  if (l < fixed_t(0)) colour = ambient_colour;
  else colour = diffuse_colour * min(fixed_t(1), l) + ambient_colour;

  return (((colour.x.val >> (FIXED_PT_PREC + 3)) & 0x001f) |
          ((colour.y.val >> (FIXED_PT_PREC + 3 - 6)) & 0x07c0) |
          ((colour.z.val >> (FIXED_PT_PREC + 3 - 11)) & 0xf800));
}

void __not_in_flash("rendering") set_colour_for_normal(const Vec3D& norm, const Material& mat)
{
  RGB565 colour = get_lit_colour(norm, mat.ambient_colour, mat.diffuse_colour);
  graphics.set_pen(colour);
}

