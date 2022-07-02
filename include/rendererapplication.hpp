#ifndef GEOCOLD_INCLUDE_APPLICATION_HPP
#define GEOCOLD_INCLUDE_APPLICATION_HPP


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//#include "rendererwindow.hpp"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

namespace geocold {

	class RenderApplication {

		public:
			void run();

		private:
			//private methods
			void initialize_window();

			void initialize_vulkan();

			void mainloop();

			void cleanup();

			void createinstance();

			void pickPhysicalDevice();

			bool isdevicesuitable(VkPhysicalDevice device);

			int ratedevicesuitability(VkPhysicalDevice device);

		private: //fields
			GLFWwindow* window;
			VkInstance instance;
			VkPhysicalDevice pdev{VK_NULL_HANDLE} ;
			uint32_t width { WIDTH };
			uint32_t height { HEIGHT };

	};


} //namespace geocold 



#endif

