#ifndef _INCLUDE_MAIN_HPP
#define _INCLUDE_MAIN_HPP

#include "global.hpp"
#include "screen.hpp"
#include "screen/map.hpp"
#include "event/handler.hpp"
#include "map.hpp"
#include "lists.hpp"

class Main {
    bool hasQuitStatus;
    Uint8 maxFPS;
    Uint8 mode;
    Uint8 subMode;
    SDL_Event event;
    Screen screen;
    EventHandler eventHandler;
    Map map;
    Lists lists;
  public:
    Main(Uint8, Uint8, Uint8);
    void handleGeneralEventSignal(Uint8);
    void handleEditorEventSignal(Uint8);
    void loop();
    void quit();
};

#endif
