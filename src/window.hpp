#pragma once

struct GLFWwindow;

namespace esc
{

    class window
    {
    public:
        window();
        window(int width, int height, const char *title);
        window(const window &) = delete;
        ~window();

        int getwidth() const noexcept { return width; }
        int getheight() const noexcept { return height; }

        void setwidth(int width);
        void setheight(int height);
        void setsize(int width, int height);

        bool is_open() const noexcept;

        void clear() const noexcept;
        void swap_buffers() const noexcept;

        void process_events() const noexcept;

        GLFWwindow* getwindow() const noexcept { return m_window; }

    private:
        int width, height;
        GLFWwindow *m_window;
    };

    class input
    {
    public:
        input(window &window) : m_window(window) {}

        int getkeydown();

        int getkeyrelease();

        int mousedown();

    private:
        window &m_window;
    };

} // namespace esc
