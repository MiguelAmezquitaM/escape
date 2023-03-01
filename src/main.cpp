
#include "game/types.hpp"
#include "game/sys/render_system.hpp"
#include "game/sys/window_system.hpp"
#include "game/sys/drag_system.hpp"
#include "game/sys/physics_system.hpp"
#include "game/sys/vectorial_field_system.hpp"
#include "game/sys/input_system.hpp"
#include <GLFW/glfw3.h>

using namespace esc;

constexpr void CreateMap(EntityManager &em, glm::vec2 Pos, glm::vec2 Size, glm::vec3 Color, glm::vec4 WallsWidth);
constexpr void CreateWall(EntityManager &em, glm::vec2 Pos, glm::vec2 Size, glm::vec3 Color);
void CreatePlayer(EntityManager &em, glm::vec2 Pos);

glm::vec2 wind(glm::vec2 point)
{
    glm::vec2 origin = {720, 480};

    float x = point.x - origin.x;
    float y = point.y - origin.y;

    float cofactor = x * x + y * y;
    return {1.0f * y / cofactor, -1.0f * x / cofactor};
}

int main()
{
    WindowSystem WindowSystem(1440, 960, "Escape!");

    VectorialFieldSystem VectorialSystem(wind);
    RenderSystem RenderSystem(WindowSystem);
    PhysicsSystem PhysicsSystem;
    InputSystem InputSystem;
    DragSystem DragSystem;

    EntityManager EMgr;

    EMgr.ReserveEntities(100);
    EMgr.ReserveComponent<RenderComponent>(100);
    EMgr.ReserveComponent<DragComponent>(100);
    EMgr.ReserveComponent<PhysicsComponent>(100);

    CreateMap(EMgr, {30, 30}, {1380, 900}, {0.51f, 0.85f, 0.95f}, {40, 40, 40, 40});
    CreatePlayer(EMgr, {1440, 960});

    for (int i = 0; i < 95; ++i)
    {
        auto &e = EMgr.MakeEntity();
        EMgr.AddComponent<RenderComponent>(e, glm::vec2{720, 480}, glm::vec2{25, 25}, glm::vec3{1.0f}, i + 1);
        EMgr.AddComponent<PhysicsComponent>(e);
    }

    while (!WindowSystem.ShouldClose())
    {
        InputSystem.Update(EMgr);
        DragSystem.Update(EMgr);
        VectorialSystem.Update(EMgr);
        PhysicsSystem.Update(EMgr);
        RenderSystem.Update(EMgr);
        WindowSystem.Update();
    }

    return 0;
}

constexpr void CreateMap(EntityManager &em, glm::vec2 Pos, glm::vec2 Size, glm::vec3 Color, glm::vec4 WallsWidth)
{
    CreateWall(em, {Pos.x, Pos.y + Size.y - WallsWidth.x}, {Size.x, WallsWidth.x}, Color);
    CreateWall(em, {Pos.x + Size.x - WallsWidth.y, Pos.y}, {WallsWidth.y, Size.y}, Color);
    CreateWall(em, Pos, {Size.x, WallsWidth.z}, Color);
    CreateWall(em, Pos, {WallsWidth.w, Size.y}, Color);
}

constexpr void CreateWall(EntityManager &em, glm::vec2 Pos, glm::vec2 Size, glm::vec3 Color)
{
    auto &entity = em.MakeEntity();
    em.AddComponent<RenderComponent>(entity, Pos, Size, Color, 0);
}

auto GetActionMovement(glm::vec2 vel, Entity &entity)
{
    return [=, &entity]()
    {
        auto &phy = entity.GetComponentRef<PhysicsComponent>();
        phy.vel = vel;
    };
}

void CreatePlayer(EntityManager &em, glm::vec2 Wsize)
{
    auto &player = em.MakeEntity();
    constexpr auto size = glm::vec2{20.0f, 30.0f};
    constexpr auto color = glm::vec3{0.95f, 0.12f, 0.11f};
    em.AddComponent<RenderComponent>(player, Wsize * 0.5f - size, size, color, 5);
    em.AddComponent<PhysicsComponent>(player);

    InputComponent inp;

    inp.actions[GLFW_KEY_W] = GetActionMovement({0.0f, 1.0f}, player);
    inp.actions[GLFW_KEY_A] = GetActionMovement({-1.0f, 0.0f}, player);
    inp.actions[GLFW_KEY_S] = GetActionMovement({0.0f, -1.0f}, player);
    inp.actions[GLFW_KEY_D] = GetActionMovement({1.0f, 0.0f}, player);

    em.AddComponent<InputComponent>(player, std::move(inp));
}
