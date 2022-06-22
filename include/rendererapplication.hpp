#ifndef GEOCOLD_INCLUDE_APPLICATION_HPP
#define GEOCOLD_INCLUDE_APPLICATION_HPP


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "rendererwindow.hpp"

namespace renderer {

	class RenderApplication {
		public:

		private:
	  	VkInstance vkinstance;
			RenderWindow window;
	};

} //namespace renderer 



#endif
