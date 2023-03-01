#pragma once

#include "../types.hpp"

namespace esc
{

  class VectorialFieldSystem
  {
  public:
    VectorialFieldSystem(std::function<glm::vec2(glm::vec2)> action) : action(action) {}

    void Update(EntityManager &em)
    {
      em.ForEach<PhysicsComponent>(
          [&](Entity &entity)
          {
            auto &ren = entity.GetComponentRef<RenderComponent>();
            auto &phy = entity.GetComponentRef<PhysicsComponent>();
            auto acc = action(ren.Coords);
            phy.vel = acc;
          });
    }

    std::function<glm::vec2(glm::vec2)> action;
  };
} // namespace esc
