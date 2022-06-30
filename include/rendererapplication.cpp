#include <stdexcept>
#include "rendererapplication.hpp"


#include <vector>
#include <map>


namespace geocold {


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
    pickPhysicalDevice();
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

  void RenderApplication::pickPhysicalDevice() {
    uint32_t devcount{0};
    vkEnumeratePhysicalDevices(instance, &devcount, nullptr);

    if (devcount == 0) {
      throw std::runtime_error("Failed to find any GPUs with vulkan support.");
    }

    std::vector<VkPhysicalDevice> devices(devcount);
    vkEnumeratePhysicalDevices(instance, &devcount, devices.data());
    
    for (const auto& device : devices) {
      if (isdevicesuitable(device)) {
        pdev = device;
        break;
      }

      if (pdev == VK_NULL_HANDLE) {
        throw std::runtime_error("Failed to find a suitable GPU!");
      }
    }

    std::multimap<int, VkPhysicalDevice> candidates;
    for (const auto& device : devices) {
      int score = rateDeviceSuitability(device);
      candidates.insert(std::make_pair(score,device));
    }
  }

  bool RenderApplication::isdevicesuitable(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties devprop;
    vkGetPhysicalDeviceProperties(device, &devprop);
    VkPhysicalDeviceFeatures devfeatures;
    vkGetPhysicalDeviceFeatures(device, &devfeatures);
    return devprop.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
                              && devfeatures.geometryShader;   
  }

  int RenderApplication::ratedevicesuitability(VkPhysicalDevice device) {
    
  }





}  //namespace geocold 
