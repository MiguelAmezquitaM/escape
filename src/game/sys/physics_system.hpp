
#pragma once

#include "../types.hpp"

namespace esc
{
  class PhysicsSystem
  {
  public:
    void Update(EntityManager &em)
    {
      em.ForEach<PhysicsComponent, RenderComponent>(
          [](Entity &e)
          {
            auto &phy = e.GetComponentRef<PhysicsComponent>();
            auto &ren = e.GetComponentRef<RenderComponent>();
            phy.vel += phy.acc;
            ren.Coords += phy.vel;
          });
    }
  };

} // namespace esc
