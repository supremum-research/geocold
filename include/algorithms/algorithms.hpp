#ifndef GEOCOLD_INCLUDE_ALGORITHMS_ALGORITHMS_HPP
#define GEOCOLD_INCLUDE_ALGORITHMS_ALGORITHMS_HPP


namespace geocold {

template <typename T>
struct Algorithm {
  virtual ~Algorithm() = default; //dtor
  Algorithm(const Algorithm&) = default; //copy ctor
  Algorithm(Algorithm&&) noexcept = default; //move ctor
  Algorithm& operator=(const Algorithm&) = default;  //copy assignment 
  Algorithm& operator=(Algorithm&&) noexcept = default; //move assignment
}



} // namespace geocold












#endif
