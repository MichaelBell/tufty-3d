#pragma once

#include "model.h"

constexpr fixed_t default_ambient_proportion { 0.2f };
constexpr fixed_t default_diffuse_proportion { 0.8f };

inline Material make_material_for_colour(const pimoroni::RGB& colour, 
                                         const fixed_t ambient_proportion = default_ambient_proportion, 
                                         const fixed_t diffuse_proportion = default_diffuse_proportion)
{
    Vec3D vcol { colour.r, colour.g, colour.b };
    return Material {
        vcol * ambient_proportion,
        vcol * diffuse_proportion
    };
}

void set_colour_for_normal(const Vec3D& norm, const Material& mat);