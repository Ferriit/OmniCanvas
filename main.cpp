#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <ctime>


int main() {
    srand(time(NULL));;
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

    SDL_Event e;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16); // prevent 100% CPU spin
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
