#ifndef GEOCOLD_INCLUDE_PRIMITIVES_POINT_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_POINT_HPP 

#include <array>

namespace geocold {

template <std::size_t Dim, typename T = double>
class Point {
  public:
    using size_type = std::size_t; using iteration_type = size_type;

    constexpr explicit Point(std::array<T,Dim> coords) : m_comps{coords} {}
    //needs to implmement addition and subtraction between points and also scalar multiplication
    
    [[nodiscard]]
    constexpr std::array<T, Dim> to_array() const {
      return this->m_comps;
    }


    //auto to_array(const Point<Dim, T>& point) {
    //  auto arr = std::array<T, Dim>();
    //  auto count = static_cast<typename Point<Dim, T>::iteration_type>(0);

    //  for (auto elem : point)  {
    //    arr[count] = elem;
    //    count += 1;
    //  }

    //  return arr;
    //}

  private: // fields
    std::array<T, Dim> m_comps; 
};



/* -------- TYPE ALIASES FOR CONVENIENCE -------- */
using Point1f = Point<1, double>;
using Point2f = Point<2, double>;
using Point3f = Point<3, double>;

using Point1f0 = Point<1, float>;
using Point2f0 = Point<2, float>;
using Point3f0 = Point<3, float>;

template <typename T>
using Point3 = Point<3,T>;
/* --------                              -------- */


} //namespace geocold


#endif
