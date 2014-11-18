#ifndef _INCLUDE_SCREEN_HPP
#define _INCLUDE_SCREEN_HPP

#include "global.hpp"
#include "surface.hpp"
#include "screen/text.hpp"
#include "screen/map.hpp"
#include "screen/list.hpp"

class Screen: public Surface {
    Uint16 width;
    Uint16 height;
    Uint8 bpp;
    Uint8 mode;
    Uint8 subMode;
    ScreenText headerText;
    ScreenText footerText;
  public:
    ScreenMap map;
    ScreenList list;
    void init(Uint16, Uint16, Uint8, Uint8, Uint8);
    void setSubMode(Uint8);
    void initMap(Map *);
    void updateFooterText();
    void resize(Uint16 s_width, Uint16 s_height);
    void update();
    void quit();
};

#endif
