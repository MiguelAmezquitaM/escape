#include "input_system.hpp"
#include <GLFW/glfw3.h>

void esc::InputSystem::Update(EntityManager &em)
{
  em.ForEach<InputComponent>(
      [](Entity &entity)
      {
        auto &input = entity.GetComponentRef<InputComponent>();
        auto window = glfwGetCurrentContext();

        bool isDefault = true;
        for (auto &action : input.actions)
        {
          if (glfwGetKey(window, action.first) == GLFW_PRESS)
          {
            action.second();
            isDefault = false;
          }
        }

        if (isDefault && input.actions[GLFW_DONT_CARE])
          input.actions[GLFW_DONT_CARE]();
      });
}