#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace esc
{
    window::window() : window(800, 600, "Default title")
    {
    }

    window::window(int width, int height, const char *title)
    {
        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        glfwMakeContextCurrent(m_window);

        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        std::cout << "[OpenGL] Attached to this program\n";
    }

    window::~window()
    {
        if (m_window)
            glfwDestroyWindow(m_window);
    }

    void window::setwidth(int width)
    {
        glfwSetWindowSize(m_window, width, height);
    }

    void window::setheight(int height)
    {
        glfwSetWindowSize(m_window, width, height);
    }

    void window::setsize(int width, int height)
    {
        glfwSetWindowSize(m_window, width, height);
    }

    bool window::is_open() const noexcept
    {
        return !glfwWindowShouldClose(m_window);
    }

    void window::clear() const noexcept
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void window::swap_buffers() const noexcept
    {
        glfwSwapBuffers(m_window);
    }

    void window::process_events() const noexcept
    {
        glfwPollEvents();
    }

    struct glfw_lib
    {
    public:
        glfw_lib()
        {
            if (glfwInit())
            {
                std::cout << "[GLFW] Loaded successfully\n";
            }
            else
            {
                std::cout << "[GLFW] Error at load\n";
            }
        }

        ~glfw_lib()
        {
            glfwTerminate();

            std::cout << "[GLFW] Unloaded\n";
        }

    } glfw_instance;

} // namespace esc
