#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


struct Transform
{
    glm::vec2 pos;
};

struct RenderComponent
{
    glm::vec2 size;
    glm::vec3 color;
};

struct VelocityComponent
{
    glm::vec2 velocity;
};
