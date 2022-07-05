#ifndef GEOCOLD_INCLUDE_PRIMITIVES_NORMAL_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_NORMAL_HPP 

#include <cassert>
#include <cmath>
//#include "vec3.hpp"

#include "definitions.hpp"

//A good ray tracer should separate the difference between a normal, a vector,
//a point and a ray.
namespace geocold {

struct Normal3 {
    float x_;
    float y_;
    float z_;



    Normal3() :x_{float(0)}, y_{float(0)}, z_{float(0)} {} 
    

    constexpr Normal3(float x_f, float y_f, float z_f) : x_{x_f}, y_{y_f}, z_{z_f} {} // constructor
    

    [[nodiscard]] constexpr float x() const noexcept { return x_; }

    [[nodiscard]] constexpr float y() const noexcept { return y_; }

    [[nodiscard]] constexpr float z() const noexcept{ return z_; }

    [[nodiscard]] constexpr float& x() noexcept { return x_; }

    [[nodiscard]] constexpr float& y() noexcept { return y_; }

    [[nodiscard]] constexpr float& z() noexcept{ return z_; }

    [[nodiscard]] constexpr Normal3 operator-() const noexcept { return Normal3{-x_, -y_, -z_}; }

    [[nodiscard]] constexpr float operator[](int idx) const;

    [[nodiscard]] constexpr float& operator[](int idx);

    [[nodiscard]] constexpr Normal3& operator+=(const Normal3& vec) noexcept;

    [[nodiscard]] constexpr Normal3& operator-=(const Normal3& vec) noexcept;

    [[nodiscard]] constexpr Normal3& operator*=(const Normal3& vec) noexcept;

    [[nodiscard]] constexpr Normal3& operator/=(const float denom);

    [[nodiscard]] constexpr Normal3 operator+(const Normal3& vec) const noexcept;

    [[nodiscard]] constexpr Normal3 operator-(const Normal3& vec) const noexcept;

    [[nodiscard]] constexpr Normal3 normalize() const;


};

} //namespace geocold


#endif
