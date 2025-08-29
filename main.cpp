#include "headers/omnicanvas.hpp"
#include <SDL3/SDL_events.h>
#include <iostream>

int update(const std::vector<SDL_Event>& events) {
    for (const auto &e : events) {
        if (e.type == SDL_EVENT_KEY_DOWN) {
            std::cout << "Key pressed: " << e.key.scancode << std::endl;
        }
    }
    return 0;
}


int start() {
    std::cout << "STARTING" << std::endl;
    return 0;
}


int main() {
    omnicanvas canvas(update, start);
    canvas.initSDL();
}
