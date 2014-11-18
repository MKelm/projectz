#ifndef _INCLUDE_MAIN_HPP
#define _INCLUDE_MAIN_HPP

#include "global.hpp"
#include "screen.hpp"
#include "events.hpp"
#include "map.hpp"

class Main {
    Uint8 maxFPS;
    Uint8 mode;
    Uint8 subMode;
    SDL_Event event;
    Screen screen;
    Events events;
    Map map;
  public:
    Main(Uint8, Uint8, Uint8);
    void loop();
    void quit();
};

#endif
