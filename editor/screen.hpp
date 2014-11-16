#ifndef _INCLUDE_SCREEN_HPP
#define _INCLUDE_SCREEN_HPP

#include "screen/text.hpp"

class Screen {
    int width;
    int height;
    int bpp;
    int mode;
    bool doUpdate;
    SDL_Surface *surface;
    ScreenText headerText;
    ScreenText footerText;
  public:
    Screen(int, int, int, int);
    void applySurface(int, int, SDL_Surface*);
    void update();
    void quit();
};

#endif
