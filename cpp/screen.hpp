#ifndef _INCLUDE_SCREEN_HPP
#define _INCLUDE_SCREEN_HPP

#include "global.hpp"
#include "screen/text.hpp"
#include "screen/map.hpp"

class Screen {
    Uint16 width;
    Uint16 height;
    Uint8 bpp;
    Uint8 mode;
    SDL_Surface *surface;
    ScreenText headerText;
    ScreenText footerText;
    ScreenMap screenMap;
  public:
    void init(Uint16, Uint16, Uint8, Uint8);
    void initMap(Map&);
    void resize(Uint16 s_width, Uint16 s_height);
    void applySurface(Uint16, Uint16, SDL_Surface*);
    void update();
    void quit();
};

#endif
