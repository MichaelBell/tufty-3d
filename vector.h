#pragma once

#include "fixedpt.h"

#define FIXED_PT_PREC 18
using fixed_t = fixed_pt<FIXED_PT_PREC>;

struct Vec2D {
  fixed_t x, y;
};

inline Vec2D operator+(const Vec2D& a, const Vec2D& b) {
  return Vec2D{ a.x + b.x, a.y + b.y };
}

inline Vec2D& operator+=(Vec2D& a, const Vec2D& b) {
  a.x += b.x; a.y += b.y;
  return a;
}

inline Vec2D operator-(const Vec2D& a, const Vec2D& b) {
  return Vec2D{ a.x - b.x, a.y - b.y };
}

inline Vec2D& operator-=(Vec2D& a, const Vec2D& b) {
  a.x -= b.x; a.y -= b.y;
  return a;
}

inline Vec2D operator*(const Vec2D& a, const Vec2D& b) {
  return Vec2D{ a.x * b.x, a.y * b.y };
}

inline Vec2D& operator*=(Vec2D& a, const Vec2D& b) {
  a.x *= b.x; a.y *= b.y;
  return a;
}

inline Vec2D operator*(const Vec2D& a, const fixed_t& b) {
  return Vec2D{ a.x * b, a.y * b };
}

inline Vec2D& operator*=(Vec2D& a, const fixed_t& b) {
  a.x *= b; a.y *= b;
  return a;
}

inline Vec2D operator<<(const Vec2D& a, const int b) {
  return Vec2D{ a.x << b, a.y << b };
}

inline Vec2D& operator<<=(Vec2D& a, const int b) {
  a.x <<= b; a.y <<= b;
  return a;
}

inline Vec2D operator>>(const Vec2D& a, const int b) {
  return Vec2D{ a.x >> b, a.y >> b };
}

inline Vec2D& operator>>=(Vec2D& a, const int b) {
  a.x >>= b; a.y >>= b;
  return a;
}

inline fixed_t Dot(const Vec2D& a, const Vec2D& b) {
  return a.x * b.x + a.y * b.y;
}

struct Vec3D {
  fixed_t x, y, z;
};

inline Vec3D operator+(const Vec3D& a, const Vec3D& b) {
  return Vec3D{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline Vec3D& operator+=(Vec3D& a, const Vec3D& b) {
  a.x += b.x; a.y += b.y; a.z += b.z;
  return a;
}

inline Vec3D operator-(const Vec3D& a, const Vec3D& b) {
  return Vec3D{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline Vec3D& operator-=(Vec3D& a, const Vec3D& b) {
  a.x -= b.x; a.y -= b.y; a.z -= b.z;
  return a;
}

inline Vec3D operator*(const Vec3D& a, const Vec3D& b) {
  return Vec3D{ a.x * b.x, a.y * b.y, a.z * b.z };
}

inline Vec3D& operator*=(Vec3D& a, const Vec3D& b) {
  a.x *= b.x; a.y *= b.y; a.z *= b.z;
  return a;
}

inline Vec3D operator*(const Vec3D& a, const fixed_t& b) {
  return Vec3D{ a.x * b, a.y * b, a.z * b };
}

inline Vec3D& operator*=(Vec3D& a, const fixed_t& b) {
  a.x *= b; a.y *= b; a.z *= b;
  return a;
}

inline Vec3D operator/(const Vec3D& a, const Vec3D& b) {
  return Vec3D{ a.x / b.x, a.y / b.y, a.z / b.z };
}

inline Vec3D& operator/=(Vec3D& a, const Vec3D& b) {
  a.x /= b.x; a.y /= b.y; a.z /= b.z;
  return a;
}

inline Vec3D operator/(const Vec3D& a, const fixed_t& b) {
  return Vec3D{ a.x / b, a.y / b, a.z / b };
}

inline Vec3D& operator/=(Vec3D& a, const fixed_t& b) {
  a.x /= b; a.y /= b; a.z /= b;
  return a;
}

inline Vec3D operator<<(const Vec3D& a, const int b) {
  return Vec3D{ a.x << b, a.y << b, a.z << b };
}

inline Vec3D& operator<<=(Vec3D& a, const int b) {
  a.x <<= b; a.y <<= b; a.z <<= b;
  return a;
}

inline Vec3D operator>>(const Vec3D& a, const int b) {
  return Vec3D{ a.x >> b, a.y >> b, a.z >> b };
}

inline Vec3D& operator>>=(Vec3D& a, const int b) {
  a.x >>= b; a.y >>= b; a.z >>= b;
  return a;
}

inline fixed_t Dot(const Vec3D& a, const Vec3D& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Dot two unit vectors, so we can use fast multiplies 
inline fixed_t DotNormals(const Vec3D& a, const Vec3D& b) {
  return unit_unit_multiply(a.x, b.x) + unit_unit_multiply(a.y, b.y) + unit_unit_multiply(a.z, b.z);
}

inline Vec3D Cross(const Vec3D& a, const Vec3D& b) {
  Vec3D v;
  v.x = a.y * b.z - a.z * b.y;
  v.y = a.z * b.x - a.x * b.z;
  v.z = a.x * b.y - a.y * b.x;
  return v; 
}

inline Vec3D Normalize(const Vec3D& a) {
  fixed_t len = Dot(a, a);
  if (len.val == 0) {
    return Vec3D{0, 0, 0};
  }

  // TODO: Need a fast reciprocal sqrt
  return a / sqrt(len);
}