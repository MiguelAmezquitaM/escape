#include "window_system.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace esc
{

  WindowSystem::WindowSystem(int width, int height, const char *title) noexcept
      : width(width), height(height)
  {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  }

  WindowSystem::~WindowSystem() noexcept
  {
    glfwMakeContextCurrent(nullptr);
    glfwDestroyWindow(window);
  }

  bool WindowSystem::ShouldClose() const noexcept
  {
    return glfwWindowShouldClose(window);
  }

  void WindowSystem::Update() const noexcept
  {
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  struct WindowLibrary
  {
    WindowLibrary()
    {
      glfwInit();
    }

    ~WindowLibrary()
    {
      glfwTerminate();
    }
  } s_WindowLibrary;

} // namespace esc
