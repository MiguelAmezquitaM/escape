#pragma once

#include <glm/glm.hpp>

namespace esc
{

  struct Rectangle
  {
    constexpr Rectangle(glm::vec2 pos, glm::vec2 size)
        : Pos(pos), Size(size) {}

    constexpr bool Contains(glm::vec2 Point)
    {
      bool retval = (Pos.x < Point.x && Point.x < Pos.x + Size.x) && (Pos.y < Point.y && Point.y < Pos.y + Size.y);
      return retval;
    }

    glm::vec2 Pos, Size;
  };
} // namespace esc
