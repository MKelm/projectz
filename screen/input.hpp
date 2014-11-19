#ifndef _INCLUDE_SCREEN_INPUT_HPP
#define _INCLUDE_SCREEN_INPUT_HPP

#include "../global.hpp"
#include "../surface.hpp"
#include "text.hpp"

class ScreenInput: public Surface {
    string textStr;
    Uint8 textFontSize;
    ScreenText titleText;
    ScreenText text;
    SDL_Rect rectBox;
  public:
    void init(string);
    void show();
    void appendChar(string);
    void removeChar();
    void unset();
};

#endif
