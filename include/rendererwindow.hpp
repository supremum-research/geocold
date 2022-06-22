
#ifndef GEOCOLD_INCLUDE_APPLICATION_HPP
#define GEOCOLD_INCLUDE_APPLICATION_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


namespace renderer {

  class RenderWindow {
    private:
      int m_a;
    public:
      RenderWindow() = default;
      explicit RenderWindow(int f_a) :m_a{f_a} {}

  };



} //namespace renderer



#endif
