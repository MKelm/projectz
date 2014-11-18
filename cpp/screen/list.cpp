#include "list.hpp"

void ScreenList::init(Uint8 pMode) {
  mode = pMode;

  scrollbarActive = false;

  imageSize = 32;
  imageMarginTop = 2;
  imageMarginRight = 4;
  titleMarginBottom = 1;
  textMarginBottom = 4;

  options.length = 7;
  options.offsetX = 0.;
  options.offsetY = 0.;
  options.selectetIdx = -1;

  // const entries for developement
  options.selectetIdx = 6;
  string *listEntries = new string[options.length];
  listEntries[0] = "Entry Empty";
  listEntries[1] = "Entry Trees";
  listEntries[2] = "Entry Rocks";
  listEntries[3] = "Entry Fishes";
  listEntries[4] = "Entry Gold";
  listEntries[5] = "Entry Coal";
  listEntries[6] = "Entry Ironore";

  entries = new stListEntry[options.length];
  int i;
  for (i = 0; i < options.length; i++) {
    entries[i].title.setFontSize(18);
    entries[i].title.set(listEntries[i]);
    entries[i].text.setFontSize(16);
    entries[i].text.set(listEntries[i]);
  }

  options.lengthY = options.length *
    (entries[0].title.getHeight() + titleMarginBottom +
     entries[0].text.getHeight() + textMarginBottom);

  delete[] listEntries;
}

void ScreenList::show() {
  Uint16 i, entryPosX, entryPosY;
  entryPosX = (Uint16)options.offsetX;
  entryPosY = (Uint16)options.offsetY;

  SDL_Rect offset;
  for (i = 0; i < options.length; i++) {
    offset.x = entryPosX;
    offset.y = entryPosY;

    if (options.selectetIdx == i) {
      boxRGBA(
        surface,
        offset.x, offset.y,
        offset.x + surface->w - 22,
        offset.y + entries[i].title.getHeight() + entries[i].text.getHeight(),
        0, 120, 180, 255
      );
    }

    /*todo images ... if (list[i].image != NULL) {
      offset.y = entry_pos_y + image_margin_top;
      SDL_BlitSurface(list[i].image, NULL, screen, &offset);
      offset.x += image_size + image_margin_right;
    } else {
      offset.x = entry_pos_x;
    }
    offset.y = entry_pos_y;*/

    apply(offset.x, offset.y, entries[i].title.get());

    entryPosY += entries[i].title.getHeight() + titleMarginBottom;
    offset.y = entryPosY;

    apply(offset.x, offset.y, entries[i].text.get());

    entryPosY += entries[i].text.getHeight() + textMarginBottom;
    offset.y = entryPosY;
  }
}

void ScreenList::unset() {
  int i;
  for (i = 0; i < options.length; i++) {
    entries[i].title.unset();
    entries[i].text.unset();
  }
  delete[] entries;
}
