#pragma once

struct GLFWwindow;

namespace esc
{

  class WindowSystem
  {
  public:
    WindowSystem(int width, int height, const char *title) noexcept;
    ~WindowSystem() noexcept;

    void Update() const noexcept;

    bool ShouldClose() const noexcept;

    int width, height;
  private:
    GLFWwindow *window;
  };

} // namespace esc
