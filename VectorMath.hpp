/* Simple Vector2/3/4 classes 
 * Author: Adam "beckadamtheinventor" Beckingham 
 * License: MIT
 */
#ifndef __VECTORMATH_HPP__
#define __VECTORMATH_HPP__

#include <cmath>

template<class T>
class Vec4 {
    public:
    T x, y, z, w;
    Vec4(T x) : Vec4(x, x, x, x) {}
    Vec4(T x, T y) : Vec4(x, y, 0, 0) {}
    Vec4(T x, T y, T z) : Vec4(x, y, z, 0) {}
    Vec4(T x, T y, T z, T w) {
        this->x = x; this->y = y; this->z = z; this->w = w;
    }
    inline T length() {
        return std::sqrt(lengthSqr());
    }
    inline T lengthSqr() {
        return x*x + y*y + z*z + w*w;
    }
    inline Vec4 operator+(Vec4 o) {
        return Vec4(x+o.x, y+o.y, z+o.z, w+o.w);
    }
    inline Vec4 operator-(Vec4 o) {
        return Vec4(x-o.x, y-o.y, z-o.z, w-o.w);
    }
    inline Vec4 operator*(Vec4 o) {
        return Vec4(x*o.x, y*o.y, z*o.z, w*o.w);
    }
    inline Vec4 operator/(Vec4 o) {
        return Vec4(x/o.x, y/o.y, z/o.z, w/o.w);
    }
    inline Vec4 operator*(T s) {
        return Vec4(x*s, y*s, z*s, w*s);
    }
    inline Vec4 operator/(T s) {
        return Vec4(x/s, y/s, z/s, w/s);
    }
};

class Vector4 : public Vec4<float> {};
class Vector4i : public Vec4<int> {};
class Vector4d : public Vec4<double> {};
class Vector4l : public Vec4<long long> {};

template<class T>
class Vec3 {
    public:
    T x, y, z;
    Vec3(T x) : Vec3(x, x, x) {}
    Vec3(T x, T y) : Vec3(x, y, 0) {}
    Vec3(T x, T y, T z) {
        this->x = x; this->y = y; this->z = z;
    }
    inline T length() {
        return std::sqrt(lengthSqr());
    }
    inline T lengthSqr() {
        return x*x + y*y + z*z;
    }
    inline Vec3 operator+(Vec3 o) {
        return Vec3(x+o.x, y+o.y, z+o.z);
    }
    inline Vec3 operator-(Vec3 o) {
        return Vec3(x-o.x, y-o.y, z-o.z);
    }
    inline Vec3 operator*(Vec3 o) {
        return Vec3(x*o.x, y*o.y, z*o.z);
    }
    inline Vec3 operator/(Vec3 o) {
        return Vec3(x/o.x, y/o.y, z/o.z);
    }
    inline Vec3 operator*(T s) {
        return Vec3(x*s, y*s, z*s);
    }
    inline Vec3 operator/(T s) {
        return Vec3(x/s, y/s, z/s);
    }
};

class Vector3 : public Vec3<float> {};
class Vector3i : public Vec3<int> {};
class Vector3d : public Vec3<double> {};
class Vector3l : public Vec3<long long> {};

template<class T>
class Vec2 {
    public:
    T x, y;
    Vec2(T x) : Vec2(x, x) {}
    Vec2(T x, T y) {
        this->x = x; this->y = y;
    }
    inline T length() {
        return std::sqrt(lengthSqr());
    }
    inline T lengthSqr() {
        return x*x + y*y;
    }
    inline Vec2 operator+(Vec2 o) {
        return Vec2(x+o.x, y+o.y);
    }
    inline Vec2 operator-(Vec2 o) {
        return Vec2(x-o.x, y-o.y);
    }
    inline Vec2 operator*(Vec2 o) {
        return Vec2(x*o.x, y*o.y);
    }
    inline Vec2 operator/(Vec2 o) {
        return Vec2(x/o.x, y/o.y);
    }
    inline Vec2 operator*(T s) {
        return Vec2(x*s, y*s);
    }
    inline Vec2 operator/(T s) {
        return Vec2(x/s, y/s);
    }
};

class Vector2 : public Vec2<float> {};
class Vector2i : public Vec2<int> {};
class Vector2d : public Vec2<double> {};
class Vector2l : public Vec2<long long> {};

#endif