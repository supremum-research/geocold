#ifndef COMPGEO_INCLUDE_COMPGEO_HPP
#define COMPGEO_INCLUDE_COMPGEO_HPP

#include <iterator>
#include <array>
#include <vector>

//namespace collections {
//template <std::size_t Dim, typename T>
//class SArray {
//  public: 
//
//  private: 
//
//
//};
//} //collections

namespace geocold {

template <std::size_t Dim, typename T = double>
class Point {
  public:
    using size_type = std::size_t; using iteration_type = size_type;

  public: //methods
    constexpr explicit Point(std::array<T,Dim> coords) : m_comps{coords} {}
    //needs to implmement addition and subtraction between points and also scalar multiplication


    auto to_array(const Point<Dim, T>& point) {
      auto arr = std::array<T, Dim>();
      auto count = static_cast<typename Point<Dim, T>::iteration_type>(0);

      for (auto i : point)  {
        arr[count] = i;
        count += 1;
      }

      return arr;
    }

    auto to_vec() {
      auto vec = std::vector<T>(); 
      auto len = m_comps.size();
      vec.reserve(len);
      auto count = static_cast<typename Point<Dim, T>::iteration_type>(0);

      for (auto i : m_comps)  {
        vec[count] = i;
        count += 1;
      }

      return vec;
    }

    auto squarel2norm() {
      auto sum = static_cast<T>(0);

      for (auto i : m_comps) {
        sum += i*i;
      } 

      return sum;
    }



  private: // fields
    std::array<T, Dim> m_comps; 
};

template <std::size_t Dim, typename T> 
struct Line {
    //fields
    Point<Dim, T> m_a; 
    Point<Dim, T> m_b;

    //methods
    constexpr Line(const Point<Dim,T>& a, const Point<Dim,T>& b) : m_a{a}, m_b{b} {}

    [[nodiscard]] //don't discard the return value, i.e. handle the return value.
    constexpr Point<Dim,T> operator()(T param) const { 
      return m_a + param * (m_b - m_a); // L : a + t*v where a, v ∈ R^{n} and t ∈ R
    }

    
};



/* -------- TYPE ALIASES FOR CONVENIENCE -------- */
using Point1f = Point<1, double>;
using Point2f = Point<2, double>;
using Point3f = Point<3, double>;

template <typename T>
using Point3 = Point<3,T>;
/* --------                              -------- */

template <std::size_t Dim, typename T>
[[nodiscard]] bool liesin(const Point<Dim, T>& point, const Line<Dim, T>& line) {
  auto d = (line.a-line.b).squarel2norm();
}


} //namespace geocold
#endif

