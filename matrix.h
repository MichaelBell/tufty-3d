#pragma once

#include "vector.h"

template<int ROWS, int COLS>
struct Matrix {
    fixed_t m[ROWS * COLS];

    fixed_t operator()(int col, int row) const {
        return m[col + row * COLS];
    }

    fixed_t& operator()(int col, int row) {
        return m[col + row * COLS];
    }
};

constexpr Matrix<3, 3> MAT_IDENTITY { 
    1, 0, 0,
    0, 1, 0,
    0, 0, 1 
};

inline Matrix<3, 3> mat_roll(float roll) {
    float cr, sr;
    sincosf(roll, &sr, &cr);
    return Matrix<3, 3> {
        cr, -sr, 0,
        sr, cr, 0,
        0, 0, 1
    };
}

inline Matrix<3, 3> mat_yaw(float yaw) {
    float cy, sy;
    sincosf(yaw, &sy, &cy);
    return Matrix<3, 3> {
        cy, 0, sy,
        0, 1, 0,
        -sy, 0, cy
    };
}

inline Matrix<3, 3> mat_pitch(float pitch) {
    float cp, sp;
    sincosf(pitch, &sp, &cp);
    return Matrix<3, 3> {
        1, 0, 0,
        0, cp, sp,
        0, -sp, cp
    };
}

template<int ROWS, int COLS>
inline Matrix<ROWS, COLS> operator+(const Matrix<ROWS, COLS>& a, const Matrix<ROWS, COLS>& b) {
    Matrix<ROWS, COLS> m;
    for (int i = 0; i < ROWS * COLS; ++i) {
        m.m[i] = a.m[i] + b.m[i];
    }
    return m;
}

template<int ROWS, int COLS>
inline Matrix<ROWS, COLS>& operator+=(Matrix<ROWS, COLS>& a, const Matrix<ROWS, COLS>& b) {
    for (int i = 0; i < ROWS * COLS; ++i) {
        a.m[i] += b.m[i];
    }
    return a;
}

template<int ROWS, int COLS>
inline Matrix<ROWS, COLS> operator-(const Matrix<ROWS, COLS>& a, const Matrix<ROWS, COLS>& b) {
    Matrix<ROWS, COLS> m;
    for (int i = 0; i < ROWS * COLS; ++i) {
        m.m[i] = a.m[i] - b.m[i];
    }
    return m;
}

template<int ROWS, int COLS>
inline Matrix<ROWS, COLS>& operator-=(Matrix<ROWS, COLS>& a, const Matrix<ROWS, COLS>& b) {
    for (int i = 0; i < ROWS * COLS; ++i) {
        a.m[i] -= b.m[i];
    }
    return a;
}

template<int ROWS, int COLS, int COLS2>
inline Matrix<ROWS, COLS2> operator*(const Matrix<ROWS, COLS>& a, const Matrix<COLS, COLS2>& b) {
    Matrix<ROWS, COLS2> m;
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS2; ++x) {
            m(x, y) = 0;
            for (int z = 0; z < COLS; ++z) {
                m(x, y) += a(z, y) * b(x, z);
            }
        }
    }
    return m;
}

template<int ROWS, int COLS>
inline Matrix<ROWS, COLS>& operator*=(Matrix<ROWS, COLS>& a, const Matrix<ROWS, COLS>& b) {
  a = a * b;
  return a;
}

inline Vec3D operator*(const Matrix<3, 3>& a, const Vec3D& b) {
    Vec3D v;
    v.x = a(0, 0) * b.x + a(1, 0) * b.y + a(2, 0) * b.z;
    v.y = a(0, 1) * b.x + a(1, 1) * b.y + a(2, 1) * b.z;
    v.z = a(0, 2) * b.x + a(1, 2) * b.y + a(2, 2) * b.z;
    return v;
}