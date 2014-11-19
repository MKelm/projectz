#ifndef _INCLUDE_SCREEN_HPP
#define _INCLUDE_SCREEN_HPP

#include "global.hpp"
#include "surface.hpp"
#include "screen/text.hpp"
#include "screen/map.hpp"
#include "screen/list.hpp"
#include "screen/input.hpp"

class Screen: public Surface {
    Uint8 mode;
    Uint8 subMode;
    ScreenText footerLeftText;
    ScreenText footerRightText;
  public:
    ScreenMap map;
    ScreenList list;
    ScreenInput input;
    void init(Uint16, Uint16, Uint8, Uint8, Uint8);
    void setSubMode(Uint8);
    void initMap(Map *);
    void updateFooterRightText();
    void resize(Uint16 s_width, Uint16 s_height, bool);
    void update();
    void quit();
};

#endif
