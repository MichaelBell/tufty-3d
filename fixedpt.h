#pragma once

#include <cmath>

template <int PT>
struct fixed_pt
{
    int val;

    fixed_pt() = default;
    fixed_pt(const int n)
        : val(n << PT)
    {}
    fixed_pt(const int i, const int frac)
        : val((i << PT) | frac)
    {}
    fixed_pt(const float f)
        : val(f * exp2f(PT))
    {}

    explicit operator int() const { return val >> PT; }
    explicit operator float() const { return float(val) * exp2f(-PT); }
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