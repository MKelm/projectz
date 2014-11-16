#ifndef _INCLUDE_MAIN_HPP
#define _INCLUDE_MAIN_HPP

#include "global.hpp"
#include "screen.hpp"

class Main {
    Uint8 maxFPS;
    Screen screen;
  public:
    Main(Uint8, Uint8);
    void loop();
    void quit();
};

#endif
