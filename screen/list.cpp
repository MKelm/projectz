#include "list.hpp"

void ScreenList::init(Uint8 pMode) {
  setMode(pMode);

  imageSize = 32;
  imageMarginTop = 2;
  imageMarginRight = 4;
  titleMarginBottom = 1;
  textMarginBottom = 4;

  rectFrame.w = surface->w * 0.5;
  rectFrame.h = surface->h * 0.5;
  rectFrame.x = surface->w / 2 - rectFrame.w / 2;
  rectFrame.y = surface->h / 2 - rectFrame.h / 2;

  options.length = 0;
  options.offsetX = 0.;
  options.offsetY = 0.;
  options.selectetIdx = 0;

  calcScrollbar();
}

void ScreenList::calcScrollbar() {
  Uint8 sliderWidth = 16;
  Uint8 sliderHeight = 16;
  float rangeStepSize = (rectFrame.h - (5 + sliderHeight)) /
    (options.lengthY - rectFrame.h);
  float stepPos = rangeStepSize * options.offsetY * -1;

  rectScrollBarSlider.x = rectFrame.x + rectFrame.w - 19;
  rectScrollBarSlider.y = rectFrame.y + 2 + (int)stepPos;
  rectScrollBarSlider.w = sliderWidth;
  rectScrollBarSlider.h = sliderHeight;

  rectScrollBar.x = rectFrame.x + rectFrame.w - 21;
  rectScrollBar.y = rectFrame.y;
  rectScrollBar.w = 20;
  rectScrollBar.h = rectFrame.h - 1;
}

void ScreenList::showScrollbar() {
  calcScrollbar();

  rectangleRGBA(
    surface, rectScrollBar.x, rectScrollBar.y,
    rectScrollBar.x + rectScrollBar.w, rectScrollBar.y + rectScrollBar.h,
    255, 255, 255, 255
  );

  boxRGBA(
    surface,
    rectScrollBarSlider.x, rectScrollBarSlider.y,
    rectScrollBarSlider.x + rectScrollBarSlider.w,
    rectScrollBarSlider.y + rectScrollBarSlider.h,
    255, 255, 255, 255
  );
}

void ScreenList::scroll(bool up, float valY) {
  if (up == true) {
    if (options.offsetY + valY <= 0)
      options.offsetY += valY;
    else
      options.offsetY = 0;
  } else {
    if (options.offsetY - valY >= -1 * (options.lengthY - rectFrame.h))
      options.offsetY -= valY;
    else
      options.offsetY = -1 * (options.lengthY - rectFrame.h);
  }
}

bool ScreenList::sliderActive(Uint16 x, Uint16 y) {
  if (x >= rectScrollBar.x && y >= rectScrollBar.y &&
      x <= rectScrollBar.x + rectScrollBar.w &&
      y <= rectScrollBar.y + rectScrollBar.h) {
    return true;
  }
  return false;
}

void ScreenList::moveSlider(Uint16 screenY) {
  float rangeStepSize = rectFrame.h / (options.lengthY - rectFrame.h);
  options.offsetY = (screenY - rectFrame.y) / rangeStepSize * -1;
}

void ScreenList::setMode(Uint8 pMode) {
  mode = pMode;
}

Uint8 ScreenList::getMode() {
  return mode;
}

void ScreenList::setEntries(Lists *lists) {
  if (mode == LIST_MODE_EDITOR_TERRAIN) {
    options.length = lists->terrainLength;
  } else if (mode == LIST_MODE_EDITOR_ITEMS) {
    options.length = lists->itemsLength;
  } else if (mode == LIST_MODE_GAME_BUILDINGS) {
    options.length = lists->buildingsLength;
  }

  entries = new stScreenListEntry[options.length];
  int i;
  string imageFile;
  for (i = 0; i < options.length; i++) {
    entries[i].title.setFontSize(18);
    entries[i].text.setFontSize(16);
    if (mode == LIST_MODE_EDITOR_TERRAIN) {
      entries[i].title.set(lists->terrain[i].title);
      entries[i].text.set(lists->terrain[i].description);
      imageFile = "images/terrain/" + lists->terrain[i].name + "_" +
        to_string(imageSize) + ".png";
    } else if (mode == LIST_MODE_EDITOR_ITEMS) {
       entries[i].title.set(lists->items[i].title);
       entries[i].text.set(lists->items[i].description);
       imageFile = "images/items/" + lists->items[i].name + "_" +
         to_string(imageSize) + ".png";
    } else if (mode == LIST_MODE_GAME_BUILDINGS) {
       entries[i].title.set(lists->buildings[i].title);
       entries[i].text.set(lists->buildings[i].description);
       imageFile = "images/buildings/" + lists->buildings[i].name + "_" +
         to_string(imageSize) + ".png";
    }
    entries[i].image = loadImage(imageFile);
  }

  options.lengthY = options.length *
    (entries[0].title.getHeight() + titleMarginBottom +
     entries[0].text.getHeight() + textMarginBottom);
}

void ScreenList::show() {
  Uint16 i;
  int entryPosX, entryPosY;
  entryPosX = rectFrame.x + options.offsetX;
  entryPosY = rectFrame.y + options.offsetY;

  SDL_Rect offset;
  for (i = 0; i < options.length; i++) {
    offset.x = entryPosX;
    offset.y = entryPosY;

    if (options.selectetIdx == i) {
      boxRGBA(
        surface,
        offset.x, offset.y,
        offset.x + rectFrame.w - 22,
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

  rectangleRGBA(
    surface,
    rectFrame.x, rectFrame.y,
    rectFrame.x + rectFrame.w, rectFrame.y + rectFrame.h,
    255, 255, 255, 255
  );
}

void ScreenList::selectEntry(Uint16 screenY) {
  Uint16 entryHeight = entries[0].title.getHeight() + titleMarginBottom +
    entries[0].text.getHeight() + textMarginBottom;
  options.selectetIdx = (-1 * options.offsetY + (screenY - rectFrame.y)) / entryHeight;
}

Uint16 ScreenList::getSelectedIdx() {
  return options.selectetIdx;
}

void ScreenList::unset() {
  int i;
  for (i = 0; i < options.length; i++) {
    entries[i].title.unset();
    entries[i].text.unset();
    free(entries[i].image);
  }
  delete[] entries;
}
