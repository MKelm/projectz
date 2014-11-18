#include "list.hpp"

void ScreenList::init(Uint8 pMode) {
  mode = pMode;

  scrollbarActive = false;

  imageSize = 32;
  imageMarginTop = 2;
  imageMarginRight = 4;
  titleMarginBottom = 1;
  textMarginBottom = 4;

  options.length = 5;
  options.offsetX = 0.;
  options.offsetY = 0.;
  options.selectetIdx = -1;

  // const entries for developement
  string *listEntries = new string[options.length];
  listEntries[0] = "grass";
  listEntries[1] = "sand";
  listEntries[2] = "dirt";
  listEntries[3] = "water";
  listEntries[4] = "rock";

  entries = new stListEntry[options.length];
  int i;
  string imageFile;
  for (i = 0; i < options.length; i++) {
    entries[i].title.setFontSize(18);
    entries[i].title.set(listEntries[i]);
    entries[i].text.setFontSize(16);
    entries[i].text.set(listEntries[i]);

    imageFile = "../images/" + listEntries[i] + "_" +
      to_string(imageSize) + ".png";
    entries[i].image = loadImage(imageFile);
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

    if (entries[i].image != NULL) {
      offset.y = entryPosY + imageMarginTop;
      apply(offset.x, offset.y, entries[i].image);
      offset.x += imageSize + imageMarginRight;
    } else {
      offset.x = entryPosX;
    }
    offset.y = entryPosY;

    apply(offset.x, offset.y, entries[i].title.get());

    entryPosY += entries[i].title.getHeight() + titleMarginBottom;
    offset.y = entryPosY;

    apply(offset.x, offset.y, entries[i].text.get());

    entryPosY += entries[i].text.getHeight() + textMarginBottom;
    offset.y = entryPosY;
  }
}

void ScreenList::selectEntry(Uint16 screenY) {
  Uint16 entryHeight = entries[0].title.getHeight() + titleMarginBottom +
    entries[0].text.getHeight() + textMarginBottom;
  options.selectetIdx = (-1 * options.offsetY + screenY) / entryHeight;
}

void ScreenList::unset() {
  int i;
  for (i = 0; i < options.length; i++) {
    entries[i].title.unset();
    entries[i].text.unset();
  }
  delete[] entries;
}
