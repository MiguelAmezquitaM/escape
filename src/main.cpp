#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>
#include <algorithm>
#include <iostream>

using Dimention = glm::vec2;
using Point = glm::vec2;
using Color = glm::ivec3;

constexpr Color White = {191, 201, 202};
constexpr Color Black = {8, 7, 14};
constexpr Color Dark = {23, 32, 42};
constexpr Color Pink = {231, 76, 60};
constexpr Color Orange = {211, 84, 0};
constexpr Color Gray = {189, 195, 199};
constexpr Color Green = {20, 143, 119};

struct Rectangle
{
    constexpr bool Contains(Point point) const noexcept;
    constexpr bool Collides(Rectangle other) const noexcept;

    Color color;
    Point position;
    Dimention dimention;
};

template <unsigned N>
constexpr void DrawRectangles(Rectangle const (&rectangles)[N]);

struct Player
{
    Rectangle *rectangle = nullptr;
    bool isSelected = false;
};

struct Scene
{
    Scene();

    Rectangle rectangles[9];

    Player player;

    Rectangle &getGameArea();

    template <typename Fun>
    void ForRectangles(Fun &&fun);

    friend void HandleDragPlayer(Scene *scene, double MouseX, double MouseY);

    friend void HandlePressPlayer(Scene *scene);

    friend void HandleReleasePlayer(Scene *scene);
};

Scene *currentScene{};

void CursorPosCallback(GLFWwindow *, double x, double y);

void MouseButtonCallback(GLFWwindow *, int button, int action, int mods);

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

int main()
{
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(900, 900, "Escape!", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    Scene scene{};

    currentScene = &scene;

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Screen coords
    glOrtho(0.0, 900.0, 900.0, 0.0, -1.0, 1.0);

    glfwSetCursorPosCallback(window, CursorPosCallback);

    glfwSetMouseButtonCallback(window, MouseButtonCallback);
#if _WIN32
    system("cls");
#else 
    system("clear");
#endif

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        // Begin draw
        DrawRectangles(scene.rectangles);
        // End draw
        glfwSwapBuffers(window);

        glfwPollEvents();

        int i = 0;

        scene.ForRectangles(
            [&](Rectangle &rect)
            {
                gotoxy(0, i + 1);
                std::cout << "Rectangle #" << i << ": ";
                if (scene.player.rectangle->Collides(rect))
                {
                    std::cout << "Collide\n";
                }
                else
                {
                    std::cout << "       \n";
                }
                i++;
            });
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

constexpr bool Rectangle::Contains(Point point) const noexcept
{
    Dimention distance = position - point;
    return 0.0f <= distance.x && distance.x <= dimention.x && 0.0f <= distance.y && distance.y <= dimention.y;
}

constexpr bool Rectangle::Collides(Rectangle other) const noexcept
{
    Dimention distance = position - other.position;
    return -dimention.x <= distance.x && distance.x <= other.dimention.x && -dimention.y <= distance.y && distance.y <= other.dimention.y;
}

template <unsigned N>
constexpr void DrawRectangles(Rectangle const (&rectangles)[N])
{
    glBegin(GL_QUADS);
    for (Rectangle const &rectangle : rectangles)
    {
        float LX = rectangle.position.x;
        float LY = rectangle.position.y;
        float RX = rectangle.position.x + rectangle.dimention.x;
        float RY = rectangle.position.y + rectangle.dimention.y;
        glColor3ub(rectangle.color.r, rectangle.color.g, rectangle.color.b);
        glVertex2f(LX, LY);
        glVertex2f(RX, LY);
        glVertex2f(RX, RY);
        glVertex2f(LX, RY);
    }
    glEnd();
}

void HandleDragPlayer(Scene *scene, double MouseX, double MouseY)
{
    Player &player = scene->player;
    Dimention &playerSize = player.rectangle->dimention;

    if (player.isSelected)
    {
        player.rectangle->position = {MouseX - playerSize.x / 2.0f, MouseY - playerSize.y / 2.0f};
    }
}

void HandlePressPlayer(Scene *scene)
{
    scene->player.isSelected = true;
}

void HandleReleasePlayer(Scene *scene)
{
    scene->player.isSelected = false;
}

void CursorPosCallback(GLFWwindow *, double x, double y)
{
    HandleDragPlayer(currentScene, x, y);
}

void MouseButtonCallback(GLFWwindow *, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            HandlePressPlayer(currentScene);
        }

        if (action == GLFW_RELEASE)
        {
            HandleReleasePlayer(currentScene);
        }
    }
}

Scene::Scene()
    : rectangles{
          {.color = Dark, .position = {0.0f, 0.0f}, .dimention = {900.0f, 900.0f}},
          {.color = White, .position = {50.0f, 50.0f}, .dimention = {800.0f, 800.0f}},
          {.color = Black, .position = {100.0f, 100.0f}, .dimention = {700.0f, 700.0f}},
          {.color = Orange, .position = {200.0f, 150.0f}, .dimention = {90.0f, 120.0f}},
          {.color = Orange, .position = {180.0f, 350.0f}, .dimention = {85.0f, 180.0f}},
          {.color = Orange, .position = {550.0f, 150.0f}, .dimention = {120.0f, 120.0f}},
          {.color = Orange, .position = {320.0f, 620.0f}, .dimention = {110.0f, 110.0f}},
          {.color = Orange, .position = {580.0f, 620.0f}, .dimention = {140.0f, 120.0f}},
          {.color = Green, .position = {400.0f, 400.0f}, .dimention = {100.0f, 100.0f}}}
{
    player.rectangle = &rectangles[8];
}

Rectangle &Scene::getGameArea()
{
    return rectangles[2];
}

template <typename Fun>
void Scene::ForRectangles(Fun &&fun)
{
    for (int i = 3; i < 8; i++)
    {
        fun(rectangles[i]);
    }
}
