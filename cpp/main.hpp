#ifndef _INCLUDE_MAIN_HPP
#define _INCLUDE_MAIN_HPP

#include "global.hpp"
#include "screen.hpp"
#include "event/handler.hpp"
#include "map.hpp"

class Main {
    bool hasQuitStatus;
    Uint8 maxFPS;
    Uint8 mode;
    Uint8 subMode;
    SDL_Event event;
    Screen screen;
    EventHandler eventHandler;
    Map map;
  public:
    Main(Uint8, Uint8, Uint8);
    void handleEditorEvents();
    void loop();
    void quit();
};

#endif
