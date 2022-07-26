#pragma once

#include <cmath>
#include <type_traits>
#include "pico/float.h"

template <int PT>
struct fixed_pt
{
    int val;

    fixed_pt() = default;
    constexpr fixed_pt(const int n)
        : val(n << PT)
    {}
    constexpr fixed_pt(const int i, const int frac)
        : val((i << PT) | frac)
    {}
    constexpr fixed_pt(const float f)
    {
        if (std::is_constant_evaluated())
        {
            val = int(f * exp2(PT));
        }
        else
        {
            val = float2fix(f, PT);
        }
    }

    explicit constexpr operator int() const { return val >> PT; }
    explicit operator float() const { return fix2float(val, PT); }
};

template <int PT>
inline fixed_pt<PT> operator+(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    fixed_pt<PT> v;
    v.val = a.val + b.val;
    return v;
}

template <int PT>
inline fixed_pt<PT>& operator+=(fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    a.val += b.val;
    return a;
}

template <int PT>
inline fixed_pt<PT> operator-(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    fixed_pt<PT> v;
    v.val = a.val - b.val;
    return v;
}

template <int PT>
inline fixed_pt<PT>& operator-=(fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    a.val -= b.val;
    return a;
}

template <int PT>
inline fixed_pt<PT> operator*(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    fixed_pt<PT> v;
    int64_t a64 = a.val;
    int64_t b64 = b.val;
    int64_t c64 = a64 * b64;
    v.val = c64 >> PT;
    return v;
}

template <int PT>
inline fixed_pt<PT>& operator*=(fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    a = a * b;
    return a;
}

template <int PT>
inline fixed_pt<PT> operator/(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    fixed_pt<PT> v;
    int64_t a64 = a.val;
    v.val = (a64 << PT) / b.val;
    return v;
}

template <int PT>
inline fixed_pt<PT>& operator/=(fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    a = a / b;
    return a;
}

template <int PT>
inline fixed_pt<PT> operator/(const fixed_pt<PT>& a, const int b)
{
    fixed_pt<PT> v;
    v.val = a.val / b;
    return v;
}

template <int PT>
inline fixed_pt<PT>& operator/=(fixed_pt<PT>& a, const int b)
{
    a.val = a.val / b;
    return a;
}

template <int PT>
inline fixed_pt<PT> operator<<(const fixed_pt<PT>& a, const int b)
{
    fixed_pt<PT> v;
    v.val = a.val << b;
    return v;
}

template <int PT>
inline fixed_pt<PT>& operator<<=(fixed_pt<PT>& a, const int b)
{
    a.val <<= b;
    return a;
}

template <int PT>
inline fixed_pt<PT> operator>>(const fixed_pt<PT>& a, const int b)
{
    fixed_pt<PT> v;
    v.val = a.val >> b;
    return v;
}

template <int PT>
inline fixed_pt<PT>& operator>>=(fixed_pt<PT>& a, const int b)
{
    a.val >>= b;
    return a;
}

template <int PT>
inline bool operator<(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    return a.val < b.val;
}

template <int PT>
inline bool operator<=(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    return a.val <= b.val;
}

template <int PT>
inline bool operator>(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    return a.val > b.val;
}

template <int PT>
inline bool operator>=(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    return a.val >= b.val;
}

template <int PT>
inline bool operator==(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    return a.val == b.val;
}

template <int PT>
inline bool operator!=(const fixed_pt<PT>& a, const fixed_pt<PT>& b)
{
    return a.val != b.val;
}

template <int PT>
inline fixed_pt<PT> sqrt(const fixed_pt<PT>& a)
{
    static_assert((PT & 1) == 0, "PT must be even");

    int q = 1;
    while (q <= a.val) q <<= 2;

    int r = 0;
    int x = a.val;
    while (q > 1) {
        q >>= 2;
        int t = x - r - q;
        r >>= 1;
        if (t >= 0) {
            x = t;
            r += q;
        }
    }

    fixed_pt<PT> rv;
    rv.val = r << (PT >> 1);
    return rv;
}