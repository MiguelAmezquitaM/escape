#pragma once

#include <glm/glm.hpp>

namespace esc
{

  struct RenderComponent
  {
    RenderComponent(glm::vec2 Coords, glm::vec2 Size, glm::vec3 Color, int zIndex)
        : Coords(Coords), Size(Size), Color(Color), zIndex(zIndex) {}

    glm::vec2 Coords;
    glm::vec2 Size;
    glm::vec3 Color;
    int zIndex{0};
  };

} // namespace esc
