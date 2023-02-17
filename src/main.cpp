
#include "application.hpp"

namespace esc
{
    class escape_game : public application
    {
    public:
        escape_game() : application(900, 900, "Escape!")
        {
        }

        void on_start() override
        {
        }

    private:
    };
} // namespace esc

int main()
{

    return 0;
}