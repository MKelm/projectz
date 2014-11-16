#ifndef _INCLUDE_SCREEN_TEXT_HPP
#define _INCLUDE_SCREEN_TEXT_HPP

class ScreenText {
    static bool hasTTF;
    string fontFile;
    string text;
  public:
    ScreenText();
    void set(string);
    void unset();
};

#endif
