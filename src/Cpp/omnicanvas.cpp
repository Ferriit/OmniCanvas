#include <vector>
#include "headers/omnicanvas.hpp"


omnicanvas::omnicanvas(int (*UpdateFunc)(const std::vector<SDL_Event>&), int (*StartFunc)()): UpdateFunc(UpdateFunc), StartFunc(StartFunc) {};

int omnicanvas::initSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("gaem", 800, 600, 0);

    if (!window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);

    this->StartFunc();

    std::vector<SDL_Event> Events;

    SDL_Event e;
    int running = 1;
    while (running) {
        Events.clear();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = 0;
            }
            else {
                Events.push_back(e);
            }
        }

        this->UpdateFunc(Events);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // prevent 100% CPU spin
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

