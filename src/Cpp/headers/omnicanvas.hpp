#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

#include <vector>


class omnicanvas {
    public:
        int (*UpdateFunc)(const std::vector<SDL_Event>&);
        int (*StartFunc)();
        omnicanvas(int (*UpdateFunc)(const std::vector<SDL_Event>&), int (*StartFunc)());

        int initSDL();
};
