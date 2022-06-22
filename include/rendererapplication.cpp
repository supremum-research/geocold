#include <stdexcept>
#include "rendererapplication.hpp"



namespace renderer {


  void RenderApplication::initialize_window() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, "Vulkan Window", nullptr, nullptr);
  }

  void RenderApplication::mainloop() {
    bool should_close = static_cast<bool>(glfwWindowShouldClose(window));
    while (!should_close) {
		  glfwPollEvents();
	  }
  }
  
  void RenderApplication::cleanup() {
    vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
		glfwTerminate();
  }

  void RenderApplication::initialize_vulkan() {
    createinstance();
  }


  void RenderApplication::createinstance() {
    //applicationinfo for creating instance
    VkApplicationInfo appinfo{};
    appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appinfo.pApplicationName = "Renderer";
    appinfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
    appinfo.pEngineName = "No Engine";
    appinfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appinfo.apiVersion = VK_API_VERSION_1_0;
  
    //set up extension count 
    uint32_t glfwExtensionCount{ 0 };
    const char** glfwExtensions{ glfwGetRequiredInstanceExtensions(&glfwExtensionCount) };


    //creating the instance
    VkInstanceCreateInfo createinfo{};
    createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createinfo.pApplicationInfo = &appinfo;
    createinfo.enabledExtensionCount = glfwExtensionCount;
    createinfo.ppEnabledExtensionNames = glfwExtensions;
    createinfo.enabledLayerCount = 0;

    auto result = vkCreateInstance(&createinfo, nullptr, &instance);

    if (result != VK_SUCCESS) {
      throw std::runtime_error("failed to create instance");
    }

  }

  void RenderApplication::run() {
		initialize_window();
		initialize_vulkan();
		mainloop();
		cleanup();
  }




}  //namespace renderer
