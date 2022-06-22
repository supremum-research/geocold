#ifndef GEOCOLD_INCLUDE_APPLICATION_HPP
#define GEOCOLD_INCLUDE_APPLICATION_HPP


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include "rendererwindow.hpp"

namespace renderer {

	const uint32_t WIDTH = 800;
	const uint32_t HEIGHT = 600;

	class RenderApplication {
		public:

			void run() {
				initialize_window();
				initialize_vulkan();
				mainloop();
				cleanup();
			}

		private:
			GLFWwindow* window;

			void initialize_window() {
				glfwInit();
				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
				glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
				window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Window", nullptr, nullptr);
			}

			void initialize_vulkan() {
				
			}

			void mainloop() {
				while (!glfwWindowShouldClose(window)) {
					glfwPollEvents();
				}
			}

			void cleanup() {
				glfwDestroyWindow(window);
				glfwTerminate();
			}
	};

} //namespace renderer 



#endif
