#pragma once

#include "window.hpp"

namespace esc
{

    class application
    {
    public:
        application(int width, int height, const char *title)
            : m_window(width, height, title), m_input(m_window)
        {
        }

        void start()
        {
            on_start();

            while (m_window.is_open())
            {
                m_window.clear();

                m_window.swap_buffers();
                m_window.process_events();
            }

            on_exit();
        }

        virtual void on_start() {}
        virtual void on_update() {}
        virtual void on_exit() {}

    protected:
        window m_window;
        input m_input;
    };

} // namespace esc
