#pragma once

#include "../ecs/entity_manager.hpp"
#include "cmp/drag_component.hpp"
#include "cmp/render_component.hpp"
#include "cmp/physics_component.hpp"
#include "cmp/input_component.hpp"

namespace esc
{
  
  using EntityManager = engine::EntityManager<DragComponent, RenderComponent, PhysicsComponent, InputComponent>;
  using Entity = typename EntityManager::Entity_t;

} // namespace esc
