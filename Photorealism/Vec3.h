#ifndef VEC3_H_
#define VEC3_H_

#include <iostream>
#include <cmath>

/// ３次元ベクトルクラス
class Vec3
{
public:
    double x, y, z;

    Vec3() { x = y = z = 0; }
    Vec3(double x) : x(x), y(x), z(x) {}
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

    /// ベクトルの長さ
    inline double length() const { return std::sqrt(length2()); }
    inline double length2() const { return x * x + y * y + z * z; }

    void operator+=(const Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
    }
};

/// ベクトル同士の演算
Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}
Vec3 operator/(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

/// ベクトルとスカラーの演算
Vec3 operator+(const Vec3& v, const double k)
{
    return Vec3(v.x + k, v.y + k, v.z + k);
}
Vec3 operator+(const double k, const Vec3& v)
{
    return v + k;
}
Vec3 operator-(const Vec3& v, const double k)
{
    return Vec3(v.x - k, v.y - k, v.z - k);
}
Vec3 operator-(const double k, const Vec3& v)
{
    return Vec3(k - v.x, k - v.y, k - v.z);
}
Vec3 operator*(const Vec3& v, const double k)
{
    return Vec3(v.x * k, v.y * k, v.z * k);
}
Vec3 operator*(const double k, const Vec3& v)
{
    return v * k;
}
Vec3 operator/(const Vec3& v, const double k)
{
    return Vec3(v.x / k, v.y / k, v.z / k);
}

/// 内積
double Dot(const Vec3& v1, const Vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/// 外積
Vec3 Cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

/// 正規化
Vec3 Normalize(const Vec3& v)
{
    return v / v.length();
}

/// コンソール出力
std::ostream& operator<<(std::ostream& stream, const Vec3& v)
{
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
}

/// 正規直交基底
void OrthonormalBasis(const Vec3& v1, Vec3& v2, Vec3& v3)
{
    if (std::abs(v1.x) > 0.9)
    {
        v2 = Vec3(0, 1, 0);
    }
    else
    {
        v2 = Vec3(1, 0, 0);
    }

    v2 = Normalize(v2 - Dot(v1, v2) * v1);
    v3 = Cross(v1, v2);
}

#endif // !VEC3_H_
