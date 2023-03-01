#pragma once

#include <glm/glm.hpp>

namespace esc
{

  struct DragComponent
  {
    DragComponent(glm::vec2 Size)
        : Size(Size) {}

    glm::vec2 Size;
    glm::vec2 CursorPos;
  };

} // namespace esc
