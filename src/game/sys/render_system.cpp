#include "render_system.hpp"
#include <glad/glad.h>

namespace esc
{
  RenderSystem::RenderSystem(WindowSystem &ws) : window(ws)
  {
  }

  void RenderSystem::Update(EntityManager &emgr)
  {
    auto &sortedEntities = emgr.FilterAndSort<RenderComponent>(
        [](Entity *a, Entity *b)
        {
          auto &renA = a->GetComponentRef<RenderComponent>();
          auto &renB = b->GetComponentRef<RenderComponent>();

          return renA.zIndex < renB.zIndex;
        });

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    for (auto entities : sortedEntities)
    {
      DrawRectangle(entities->GetComponentRef<RenderComponent>());
    }
    glEnd();
  }

  glm::vec2 RenderSystem::ScreenCoords(glm::vec2 WorldCoords)
  {
    return glm::vec2(
        (WorldCoords.x + 1.0f) / 2.0f * float(window.width),
        (WorldCoords.y + 1.0f) / 2.0f * float(window.height));
  }

  glm::vec2 RenderSystem::WorldCoords(glm::vec2 ScreenCoords)
  {
    return glm::vec2(
        ScreenCoords.x / float(window.width) * 2.0f - 1.0f,
        ScreenCoords.y / float(window.height) * 2.0f - 1.0f);
  }

  glm::vec2 RenderSystem::WorldSize(glm::vec2 ScreenSize)
  {
    return glm::vec2(
        ScreenSize.x / float(window.width) * 2.0f,
        ScreenSize.y / float(window.height) * 2.0f);
  }

  void RenderSystem::DrawRectangle(RenderComponent const &Rect)
  {
    glm::vec2 Coords = WorldCoords(Rect.Coords);
    glm::vec2 Size = WorldSize(Rect.Size);

    glColor3f(Rect.Color.r, Rect.Color.g, Rect.Color.b);
    glVertex2f(Coords.x, Coords.y);
    glVertex2f(Coords.x + Size.x, Coords.y);
    glVertex2f(Coords.x + Size.x, Coords.y + Size.y);
    glVertex2f(Coords.x, Coords.y + Size.y);
  }

} // namespace esc
