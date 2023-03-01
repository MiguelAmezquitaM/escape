#include "drag_system.hpp"
#include <GLFW/glfw3.h>

namespace esc
{
  void DragSystem::Update(EntityManager &emgr)
  {
    static int nextZIndex = static_cast<int>(emgr.GetContainer<RenderComponent>().size()) + 0x1;

    CursorState cursorState = GetCursorState();

    if (!cursorState.Pressed)
    {
      currentDragging = nullptr;
      return;
    }

    if (currentDragging)
    {
      auto &ren = currentDragging->GetComponentRef<RenderComponent>();
      auto &drag = currentDragging->GetComponentRef<DragComponent>();
      ren.Coords = cursorState.Position - drag.CursorPos;
      ren.zIndex = nextZIndex++;
      return;
    }

    auto &sortedEntities = emgr.FilterAndSort<DragComponent, RenderComponent>(
        [](Entity *a, Entity *b)
        {
          auto &renA = a->GetComponentRef<RenderComponent>();
          auto &renB = b->GetComponentRef<RenderComponent>();

          return renA.zIndex > renB.zIndex;
        });

    for (auto entity : sortedEntities)
    {
      if (currentDragging)
        break;

      auto &drag = entity->GetComponentRef<DragComponent>();
      auto &render = entity->GetComponentRef<RenderComponent>();

      Rectangle DragZone(render.Coords, drag.Size);

      if (!DragZone.Contains(cursorState.Position))
        continue;

      drag.CursorPos = cursorState.Position - render.Coords;
      currentDragging = entity;
    }
  }

  DragSystem::CursorState DragSystem::GetCursorState()
  {
    CursorState cursorState;

    glm::dvec2 CursorPos;
    GLFWwindow *window = glfwGetCurrentContext();
    int windowheight;
    glfwGetWindowSize(window, nullptr, &windowheight);
    glfwGetCursorPos(window, &CursorPos.x, &CursorPos.y);

    CursorPos.y = windowheight - CursorPos.y;

    cursorState.Position = CursorPos;
    cursorState.Pressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

    return cursorState;
  }

} // namespace esc
