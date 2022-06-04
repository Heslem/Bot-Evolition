#include <chrono>
#include <thread>

#include "graphics_mode.h"
#if GRAPHICS_MODE
#include "graphics_worker.h"
#endif
#include "world.h"

int main()
{
    const std::chrono::milliseconds timescale(1);

#if GRAPHICS_MODE
    buffer_init();
#endif

    world* mainWorld = new world();
    while (true) {

#if GRAPHICS_MODE
        clear_screen();
        buffer_clear();
        buffer_draw_gameObjects(mainWorld->gameObjects);

       /* for (size_t i = 0; i < world_size_x; i++)
        {
            for (size_t y = 0; y < world_size_y; y++)
            {
                if (mainWorld->is_busy_cell(i, y)) buffer_set_pixel(i, y, 'P');
            }
        }*/

        print_buffer();
#endif

        mainWorld->update();
        std::this_thread::sleep_for(timescale);
    }
    delete mainWorld;

    return 0;
}