#ifndef GEOCOLD_INCLUDE_PRIMITIVES_LIGHT_HPP 
#define GEOCOLD_INCLUDE_PRIMITIVES_LIGHT_HPP 


#include <iterator>
#include <array>
#include <vector>

#include "point.hpp"

namespace geocold {


template <std::size_t Dim, typename T> 
class Line {
private: 
    //fields
    Point<Dim, T> m_a; 
    Point<Dim, T> m_b;
public:

    //methods
    constexpr Line(const Point<Dim,T>& a_, const Point<Dim,T>& b_) : m_a{a_}, m_b{b_} {}

    [[nodiscard]] //don't discard the return value, i.e. handle the return value.
    constexpr Point<Dim,T> operator()(T param) const { 
      return m_a + param * (m_b - m_a); // L : a + t*v where a, v ∈ R^{n} and t ∈ R
    }

    
};





} //namespace geocold



#endif

