#include <signal.h>
#include <chrono>
#include <thread>

#include "world.h"
#include "graphics_mode.h"

#if GRAPHICS_MODE
#include "graphics_worker.h"
#endif

static bool flag = true;
void stop_world(int sig) {
    flag = false;
}

int main(int argc, char* argv[])
{
    signal(SIGINT, stop_world);

    const std::chrono::milliseconds timescale(1);

    world* currentWorld = new world();
    

#if GRAPHICS_MODE
        graphics_worker* graphics = new graphics_worker();
#endif    

    flag = true;
    while (flag) {

#if GRAPHICS_MODE

        clear_screen();
        graphics->clear_buffer();

        for (size_t i = 0; i < currentWorld->game_objects.size(); ++i)
        {
            graphics->set_pixel(currentWorld->game_objects[i]->position.get_x(), currentWorld->game_objects[i]->position.get_y(), currentWorld->game_objects[i]->sprite_);
        }

        graphics->print_buffer();
#endif

         currentWorld->update();
         // std::this_thread::sleep_for(timescale);
    }

#if GRAPHICS_MODE
    delete graphics;
#endif


    delete currentWorld;

    return 0;
}