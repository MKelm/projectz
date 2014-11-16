#ifndef _INCLUDE_SCREEN_HPP
#define _INCLUDE_SCREEN_HPP

#include "screen/text.hpp"

class Screen {
    int width;
    int height;
    int bpp;
    bool update;
    SDL_Surface *surface;
    ScreenText headerText;
    ScreenText footerText;
  public:
    Screen(int, int, int, int);
    ~Screen();
};

#endif
