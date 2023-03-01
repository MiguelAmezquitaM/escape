#pragma once

#include "../types.hpp"
#include "../rectangle.hpp"
#include <glm/glm.hpp>

namespace esc
{

  class DragSystem
  {
  public:
    void Update(EntityManager &emgr);    

    struct CursorState
    {
      glm::vec2 Position;
      int Pressed;
    };

    static CursorState GetCursorState();

  private:
    Entity* currentDragging{nullptr};
  };

} // namespace esc
