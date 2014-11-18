#ifndef _INCLUDE_SCREEN_TEXT_HPP
#define _INCLUDE_SCREEN_TEXT_HPP

#include "../global.hpp"
#include "../surface.hpp"

class ScreenText: public Surface {
    static bool hasTTF;
    string text;
    TTF_Font *font;
    Uint8 fontSize;
    string fontFile;
    struct stFontColor {
      Uint8 r;
      Uint8 g;
      Uint8 b;
      Uint8 a;
    } fontColor;
  public:
    ScreenText();
    void initTTF();
    void set(string);
    void unset();
    void quitTTF();
};

#endif
