#pragma once

#ifndef __EMSCRIPTEN__
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#endif
#include <vector>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

struct OCEvent {
    #ifndef __EMSCRIPTEN__
    SDL_Event event;
    #endif
    #ifdef __EMSCRIPTEN__
    std::vector<std::string> event;
    #endif
};

class omnicanvas {
    public:
        int (*UpdateFunc)(const std::vector<OCEvent>&);
        int (*StartFunc)();
        omnicanvas(int (*UpdateFunc)(const std::vector<OCEvent>&), int (*StartFunc)());

        #ifndef __EMSCRIPTEN__
        int initSDL();
        #endif

        #ifdef __EMSCRIPTEN__
        int initWASM();
        #endif
};
