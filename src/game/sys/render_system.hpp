#pragma once

#include "../types.hpp"
#include "window_system.hpp"

namespace esc
{

  class RenderSystem
  {
  public:
    RenderSystem(WindowSystem &ws);

    void Update(EntityManager &emgr);

  private:
    WindowSystem &window;

  private:
    glm::vec2 ScreenCoords(glm::vec2 WorldCoords);
    glm::vec2 WorldCoords(glm::vec2 ScreenCoords);
    glm::vec2 WorldSize(glm::vec2 ScreenSize);
    void DrawRectangle(RenderComponent const &rend);
  };

} // namespace esc
