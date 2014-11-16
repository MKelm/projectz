#ifndef _INCLUDE_MAIN_HPP
#define _INCLUDE_MAIN_HPP

#include "global.hpp"
#include "screen.hpp"
#include "events.hpp"

class Main {
    Uint8 maxFPS;
    Uint8 mode;
    Uint8 subMode;
    Screen screen;
    Events events;
  public:
    Main(Uint8, Uint8, Uint8);
    void loop();
    void quit();
};

#endif
