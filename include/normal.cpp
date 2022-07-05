#include "normal.hpp"


namespace geocold {


[[nodiscard]] constexpr float Normal3::operator[](int idx) const { 
  assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
  return idx == 0 ?  x_ 
                  : idx == 1 ? y_
                  : z_;
}

[[nodiscard]] constexpr float& Normal3::operator[](int idx) { 
  assert(idx < static_cast<int>(3) && idx >= static_cast<int>(0));
  return idx == 0 ?  x_ 
                  : idx == 1 ? y_
                  : z_;
}

[[nodiscard]] constexpr Normal3& Normal3::operator+=(const Normal3& vec) noexcept {
  x_ += vec.x();
  y_ += vec.y();
  z_ += vec.z();
  return *this;
}

[[nodiscard]] constexpr Normal3& Normal3::operator-=(const Normal3& vec) noexcept {
  x_ -= vec.x();
  y_ -= vec.y();
  z_ -= vec.z();
  return *this;
}

[[nodiscard]] constexpr Normal3& Normal3::operator*=(const Normal3& vec) noexcept {
  x_ *= vec.x();
  y_ *= vec.y();
  z_ *= vec.z();
  return *this;
}

[[nodiscard]] constexpr Normal3& Normal3::operator/=(const float denom) {
    x_ *= 1/denom;
    y_ *= 1/denom;
    z_ *= 1/denom;
    return *this;
}

[[nodiscard]] constexpr Normal3 Normal3::operator+(const Normal3& vec) const noexcept {
  Normal3 temp = Normal3{this->x(), this->y(), this->z()};
  temp += vec;
  return temp;
}

[[nodiscard]] constexpr Normal3 Normal3::operator-(const Normal3& vec) const noexcept {
  Normal3 temp = Normal3{this->x(), this->y(), this->z()};
  temp -= vec;
  return temp;
}

[[nodiscard]] constexpr Normal3 Normal3::normalize() const {
  auto norm = std::sqrt(this->x_*this->x_ + this->y_ * this->y_ + this->z_ * this->z_);
  return Normal3{
    this->x_ / norm,
    this->y_ / norm,
    this->z_ / norm
  };
}





} //namespace geocold 
