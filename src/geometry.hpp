#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

template <int size, typename Type> 
struct Point;

using Point3D = Point<3, float>;

struct Point2D
{
    float values[2] {};

    Point2D() {}
    Point2D(float x, float y) : values { x, y } {}

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    Point2D& operator+=(const Point2D& other)
    {
        x() += other.x();
        y() += other.y();
        return *this;
    }

    Point2D& operator*=(const Point2D& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }

    Point2D& operator*=(const float scalar)
    {
        x() *= scalar;
        y() *= scalar;
        return *this;
    }

    Point2D operator+(const Point2D& other) const
    {
        Point2D result = *this;
        result += other;
        return result;
    }

    Point2D operator*(const Point2D& other) const
    {
        Point2D result = *this;
        result *= other;
        return result;
    }

    Point2D operator*(const float scalar) const
    {
        Point2D result = *this;
        result *= scalar;
        return result;
    }
};
/*
struct Point3D
{
    // float values[3] {};
    std::array<float, 3> values;

    Point3D() {}
    Point3D(float x, float y, float z) : values { x, y, z } {}

    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    float& z() { return values[2]; }
    float z() const { return values[2]; }

    Point3D& operator+=(const Point3D& other)
    {
        std::transform(other.values.begin(), other.values.end(), values.begin(), values.begin(),
                       [](float c1, float c2) { return c1 + c2; });
        return *this;
    }

    Point3D& operator-=(const Point3D& other)
    {
        std::transform(other.values.begin(), other.values.end(), values.begin(), values.begin(),
                       [](float c1, float c2) { return c2 - c1; });
        return *this;
    }

    Point3D& operator*=(const float scalar)
    {
        std::for_each(values.begin(), values.end(), [scalar](float& value) { value *= scalar; });
        return *this;
    }

    Point3D operator+(const Point3D& other) const
    {
        Point3D result = *this;
        result += other;
        return result;
    }

    Point3D operator-(const Point3D& other) const
    {
        Point3D result = *this;
        result -= other;
        return result;
    }

    Point3D operator*(const float scalar) const
    {
        Point3D result = *this;
        result *= scalar;
        return result;
    }

    Point3D operator-() const { return Point3D { -x(), -y(), -z() }; }

    float length() const
    {
        return std::sqrt(std::accumulate(values.begin(), values.end(), 0.f,
                                         [](float acc, float c) { return acc + (c * c); }));
    }

    float distance_to(const Point3D& other) const { return (*this - other).length(); }

    Point3D& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point3D& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};
*/

template <int size, typename Type> struct Point
{

    std::array<Type, size> values {};

    Point() {}
    Point(Type x, Type y) : values { x, y } {}
    Point(Type x, Type y, Type z) : values { x, y, z } {}
    
    float& x() { return values[0]; }
    float x() const { return values[0]; }

    float& y() { return values[1]; }
    float y() const { return values[1]; }

    float& z() { return values[2]; }
    float z() const { return values[2]; }

    Point& operator+=(const Point& other)
    {
        std::transform(other.values.begin(), other.values.end(), values.begin(), values.begin(),
                       [](Type c1, Type c2) { return c1 + c2; });
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(other.values.begin(), other.values.end(), values.begin(), values.begin(),
                       [](Type c1, Type c2) { return c2 - c1; });
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        std::transform(other.values.begin(), other.values.end(), values.begin(), values.begin(),
                       [](Type c1, Type c2) { return c2 * c1; });
        return *this;
    }

    Point& operator*=(const Type scalar)
    {
        std::for_each(values.begin(), values.end(), [scalar](Type& c) { return c * scalar; });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const{
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator-() const {
        Point result = *this;
        result *= -1;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point operator*(const Type scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Type length() const
    {
        return std::sqrt(std::accumulate(values.begin(), values.end(), static_cast<Type> (0),
                                         [](Type acc, Type c) { return acc + (c * c); }));
    }

    Type distance_to(const Point& other) const { return (*this - other).length(); }

    Point& normalize(const Type target_len = static_cast<Type> (1))
    {
        const Type current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const Type max_len)
    {
        assert(max_len > 0);

        const Type current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};

inline void test_generic_points()
{
    Point<3, float> p1;
    Point<3, float> p2;
    auto p3 = p1 + p2;
    p1 += p2;
    p3 *= 3.f; // ou 3.f, ou 3.0 en fonction du type de Point
}

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
