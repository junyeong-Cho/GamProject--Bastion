#include <doodle/doodle.hpp>
#include <string>

using namespace doodle;

int main(void)
{
    create_window("Orange Window");

    using namespace std::string_literals;
    const std::string text = "("s + std::to_string(Width) + ","s + std::to_string(Height) + ")"s;


    while (!is_window_closed())
    {
        update_window();
        clear_background(HexColor{ 0xC75023FF });
        draw_text(text, 0, 0);
    }


    return 0;
}