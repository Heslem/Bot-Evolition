#include <chrono>
#include <thread>

#include "graphics_mode.h"

#if GRAPHICS_MODE
#include "graphics_worker.h"
#endif
#include "world.h"
#include "signal.h"

volatile sig_atomic_t flag = 1;
void closing_app(int sig) {
    flag = 0;
}

int main(int argc, char *argv[])
{
    signal(SIGINT, closing_app);

#if GRAPHICS_MODE
    buffer_init();
#endif

    std::chrono::milliseconds timescale(1);

    world* mainWorld = new world();

    while (flag == 1) {

#if GRAPHICS_MODE
        clear_screen();
        buffer_clear();

        buffer_draw_gameObjects(mainWorld->gameObjects);

        print_buffer();
#endif

        mainWorld->update();
        std::this_thread::sleep_for(timescale);
    }
    delete mainWorld;

    return 0;
}