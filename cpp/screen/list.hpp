#ifndef _INCLUDE_SCREEN_LIST_HPP
#define _INCLUDE_SCREEN_LIST_HPP

#include "../global.hpp"
#include "../surface.hpp"
#include "../lists.hpp"
#include "text.hpp"

enum {
  LIST_MODE_EDITOR_TERRAIN,
  LIST_MODE_EDITOR_ITEMS
};

#define LIST_MAX_ENTRIES 1024

struct stScreenListEntry {
  ScreenText title;
  ScreenText text;
  SDL_Surface *image;
};

struct stScreenListOptions {
  Uint16 length;
  Uint16 selectetIdx;
  float offsetX;
  float offsetY;
  float lengthY;
};

class ScreenList: public Surface {
    Uint8 mode;
    SDL_Rect rectScrollBar;
    SDL_Rect rectScrollBarSlider;
    bool scrollbarActive;
    Uint8 imageSize;
    Uint8 imageMarginTop;
    Uint8 imageMarginRight;
    Uint8 titleMarginBottom;
    Uint8 textMarginBottom;
    stScreenListEntry *entries;
    stScreenListOptions options;
  public:
    void init(Uint8);
    void setMode(Uint8);
    Uint8 getMode();
    void setEntries(Lists *);
    void show();
    void selectEntry(Uint16 screenY);
    Uint16 getSelectedIdx();
    void unset();
};

#endif
