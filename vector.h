// Fixed point, 16-bit.16-bit vector classes

inline int fixed_mul(int a, int b) {
  int64_t a64 = a;
  int64_t b64 = b;
  int64_t c64 = a64 * b64;
  return int(c64 >> 18);
}

struct Vec2D {
  int x, y;
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
  return Vec2D{ 
    fixed_mul(a.x, b.x),
    fixed_mul(a.y, b.y)
  };
}

inline Vec2D& operator*=(Vec2D& a, const Vec2D& b) {
  a = a * b;
  return a;
}

inline Vec2D operator*(const Vec2D& a, const int b) {
  return Vec2D{
    fixed_mul(a.x, b),
    fixed_mul(a.y, b)
  };
}

inline Vec2D& operator*=(Vec2D& a, const int b) {
  a = a * b;
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

struct Vec3D {
  int x, y, z;
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
  return Vec3D{ 
    fixed_mul(a.x, b.x),
    fixed_mul(a.y, b.y),
    fixed_mul(a.z, b.z)
  };
}

inline Vec3D& operator*=(Vec3D& a, const Vec3D& b) {
  a = a * b;
  return a;
}

inline Vec3D operator*(const Vec3D& a, const int b) {
  return Vec3D{
    fixed_mul(a.x, b),
    fixed_mul(a.y, b),
    fixed_mul(a.z, b)
  };
}

inline Vec3D& operator*=(Vec3D& a, const int b) {
  a = a * b;
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

