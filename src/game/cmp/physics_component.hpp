#pragma once

#include <glm/glm.hpp>

namespace esc
{

  struct PhysicsComponent
  {
    glm::vec2 vel{0.0f}, acc{0.0f};
  };

} // namespace esc
