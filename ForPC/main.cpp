#include <chrono>
#include <thread>

#include "graphics_mode.h"
#if GRAPHICS_MODE
#include "graphics_worker.h"
#endif
#include "world.h"
#include <signal.h>

bool flag = true;
void closing_app(int sig) {
    flag = false;
}

int main()
{
    signal(SIGINT, closing_app); // when user press CTRL + C, stopping the sumilation.
    const std::chrono::milliseconds timescale(1);

#if GRAPHICS_MODE
    buffer_init();
#endif

    world* current_world = new world();
    while (flag) {

#if GRAPHICS_MODE
        clear_screen();
        buffer_clear();
        buffer_draw_gameObjects(current_world->gameObjects);


        print_buffer();
#endif

        current_world->update();
        std::this_thread::sleep_for(timescale);
    }
    delete current_world;

    return 0;
}