#ifndef _INCLUDE_SCREEN_HPP
#define _INCLUDE_SCREEN_HPP

#include "global.hpp"
#include "screen/text.hpp"

class Screen {
    Uint16 width;
    Uint16 height;
    Uint8 bpp;
    Uint8 mode;
    Uint8 maxFPS;
    SDL_Surface *surface;
    ScreenText headerText;
    ScreenText footerText;
  public:
    void init(Uint16, Uint16, Uint8, Uint8);
    void applySurface(Uint16, Uint16, SDL_Surface*);
    void update();
    void loop();
    void quit();
};

#endif
