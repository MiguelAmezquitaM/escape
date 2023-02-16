#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>
#include <algorithm>
#include <iostream>

template <typename T>
constexpr int length(T &&e)
{
    return sizeof(e) / sizeof(e[0]);
}

constexpr int width = 800;
constexpr int height = 800;
constexpr float aspect = float(width) / height;

void draw_map();

void draw_rectangles();

void move_rectangles(float dt);

void process_input();

void game_rules();

int main()
{
    glfwInit();

    auto win = glfwCreateWindow(width, height, "Escape!", nullptr, nullptr);

    glfwMakeContextCurrent(win);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    double past_time = glfwGetTime();
    double start_time = glfwGetTime();

    while (!glfwWindowShouldClose(win))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        draw_map();

        draw_rectangles();

        move_rectangles(glfwGetTime() - past_time);
        past_time = glfwGetTime();

        process_input();

        game_rules();

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    double end_time = glfwGetTime();

    std::cout << "Tu duracion: " << end_time - start_time << " segundos\n";

    glfwDestroyWindow(win);

    glfwTerminate();

    return 0;
}

glm::vec2 screen2world(glm::vec2 P)
{
    return {
        P.x / width * 2.0f - 1.0f,
        (height - P.y) / height * 2.0f - 1.0f};
}

struct map
{
    glm::vec2 dimension;
    glm::vec2 center;
    glm::vec3 color;

    bool contains(glm::vec2 p)
    {
        return (
            center.x - dimension.x / 2.0f < p.x && p.x < center.x + dimension.x / 2.0f &&
            center.y - dimension.y / 2.0f < p.y && p.y < center.y + dimension.y / 2.0f);
    }

    glm::vec2 get_limits_x()
    {
        return {center.x - dimension.x / 2.0f, center.x + dimension.x / 2.0f};
    }

    glm::vec2 get_limits_y()
    {
        return {center.y - dimension.y / 2.0f, center.y + dimension.y / 2.0f};
    }
};

map maps[]{
    {{1.8f, 1.8f},
     {0.0f, 0.0f},
     {0.1f, 0.1f, 0.15f}},
    {{1.5f, 1.5f},
     {0.0f, 0.0f},
     {0.2f, 0.2f, 0.3f}}};

void draw_rectangle(glm::vec2 center, glm::vec2 dims, glm::vec3 color)
{
    glColor3fv(&color.x);

    float xh = center.x + dims.x / 2.0f;
    float xl = center.x - dims.x / 2.0f;
    float yh = center.y + dims.y / 2.0f;
    float yl = center.y - dims.y / 2.0f;
    glBegin(GL_QUADS);

    glVertex2f(xh, yh);
    glVertex2f(xl, yh);
    glVertex2f(xl, yl);
    glVertex2f(xh, yl);
    glEnd();
}

void draw_map()
{
    for (auto p : maps)
    {
        draw_rectangle(p.center, p.dimension, p.color);
    }
}

struct rectangle
{
    glm::vec3 color;
    glm::vec2 position;
    glm::vec2 dimention;
    glm::vec2 velocity;

    bool contains(glm::vec2 p)
    {
        return (
            position.x - dimention.x / 2.0f < p.x && p.x < position.x + dimention.x / 2.0f &&
            position.y - dimention.y / 2.0f < p.y && p.y < position.y + dimention.y / 2.0f);
    }

    float maxX()
    {
        return position.x + dimention.x / 2.0f;
    }

    float minX()
    {
        return position.x - dimention.x / 2.0f;
    }

    float maxY()
    {
        return position.y + dimention.y / 2.0f;
    }

    float minY()
    {
        return position.y - dimention.y / 2.0f;
    }
};

rectangle rectangles[]{
    {
        {0.8, 0.9, 0.7},
        {0.3, 0.32},
        {0.3, 0.1},
        {-100.0, -50.0},
    },
    {
        {0.8, 0.9, 0.7},
        {-0.4, 0.5},
        {0.25, 0.25},
        {60.0, -65.0},
    },
    {
        {0.8, 0.9, 0.7},
        {-0.4, -0.5},
        {0.2, 0.3},
        {75.0, 85.0},
    },
    {
        {0.8, 0.9, 0.7},
        {0.4, -0.6},
        {0.3, 0.15},
        {-110.0, 95.0},
    },
    {
        {1.0, 1.0, 1.0},
        {0.0, 0.0},
        {0.15, 0.15},
        {0.0, 0.0},
    }};

void draw_rectangles()
{
    for (auto rect : rectangles)
    {
        draw_rectangle(rect.position, rect.dimention, rect.color);
    }
}

void move_rectangles(float dt)
{
    auto wall = maps[0];
    auto xLimits = wall.get_limits_x();
    auto yLimits = wall.get_limits_y();

    for (auto &rect : rectangles)
    {
        rect.position += (rect.velocity / glm::vec2(width, height)) * (dt * 2.5f);

        if (rect.minX() < xLimits.x || rect.maxX() > xLimits.y)
            rect.velocity.x = -rect.velocity.x;

        if (rect.minY() < yLimits.x || rect.maxY() > yLimits.y)
            rect.velocity.y = -rect.velocity.y;
    }
}

void process_input()
{
    static bool isMoving = false;

    auto win = glfwGetCurrentContext();

    auto pressed = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_1);

    if (!pressed)
    {
        isMoving = false;
        return;
    }

    double x, y;

    glfwGetCursorPos(win, &x, &y);

    auto &player = rectangles[length(rectangles) - 1];

    glm::vec2 cursorPos = screen2world({x, y});

    if (!isMoving)
    {
        if (player.contains(cursorPos))
        {
            isMoving = true;
        }
    }

    if (!isMoving)
        return;

    auto limits = maps[1].dimension * 0.5f;

    player.position = glm::vec2(
        std::clamp(cursorPos.x, -limits.x, limits.x),
        std::clamp(cursorPos.y, -limits.y, limits.y));
}

void game_rules()
{
    auto &player = rectangles[length(rectangles) - 1];

    for (auto &rect : rectangles)
    {
        if (&rect == &player)
            continue;

        if (
            std::fabs(player.minX() - rect.minX()) < std::min(rect.dimention.x, player.dimention.x) &&
            std::fabs(player.minY() - rect.minY()) < std::min(rect.dimention.y, player.dimention.y))
        {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), true);
        }
    }
}
