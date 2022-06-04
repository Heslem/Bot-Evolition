#include <chrono>
#include <thread>

#include "graphics_worker.h"
#include "world.h"
#include "signal.h"

volatile sig_atomic_t flag = 1;
volatile sig_atomic_t draw = 1;
void closing_app(int sig) {
    flag = 0;
}

void change_draw(int sig) {
    draw = -draw;
}

int main(int argc, char *argv[])
{
    if (argc != 0) draw = -1;
    signal(SIGINT, closing_app);
    signal(SIGTSTP, change_draw);
    std::chrono::milliseconds timescale(1);

    world* mainWorld = new world();

    while (flag == 1) {

        mainWorld->update();

        if (draw == 1) {
            clear_screen();
            clear_buffer(' ');

            buffer_draw_gameObjects(mainWorld->gameObjects);

            print_buffer();
        }
        std::this_thread::sleep_for(timescale);
    }
    delete mainWorld;

    return 0;
}