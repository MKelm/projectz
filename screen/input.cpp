#include "input.hpp"

void ScreenInput::init(string titleStr) {
  textStr = "";
  textFontSize = 26;

  text.setFontSize(textFontSize);
  text.set(textStr);
  titleText.setFontSize(textFontSize);
  titleText.set(titleStr);

  resize();
}

void ScreenInput::resize() {
  rectBox.w = surface->w * 0.5;
  rectBox.h = surface->h * 0.2;
  rectBox.x = surface->w / 2 - rectBox.w / 2;
  rectBox.y = surface->h / 2 - rectBox.h / 2;
}

string ScreenInput::getTextStr() {
  return (textStr == "") ? "0" : textStr;
}

void ScreenInput::setTextStr(string pTextStr) {
  textStr = (pTextStr == "0") ? "" : pTextStr;
  text.set(textStr);
}

void ScreenInput::show() {
  boxRGBA(
    surface,
    rectBox.x, rectBox.y,
    rectBox.x + rectBox.w, rectBox.y + rectBox.h,
    0, 0, 0, 255
  );
  apply(
    rectBox.x + rectBox.w / 2 - titleText.getWidth() / 2,
    rectBox.y + titleText.getHeight() / 2,
    titleText.get()
  );
  Uint16 titleTextHeight = textFontSize;
  if (textStr.length() > 0) {
    apply(
      rectBox.x + rectBox.w / 2 - text.getWidth() / 2,
      rectBox.y + titleText.getHeight() * 2,
      text.get()
    );
    titleTextHeight = titleText.getHeight();
  }
  hlineColor(
    surface,
    rectBox.x + rectBox.w * 0.1, rectBox.x + rectBox.w * 0.9,
    rectBox.y + titleText.getHeight() * 2 + titleTextHeight,
    0xFFFFFFFF
  );
}

void ScreenInput::appendChar(string pStr) {
  textStr += pStr;
  text.set(textStr);
}

void ScreenInput::removeChar() {
  if (textStr.length() > 0) {
    textStr = textStr.substr(0, textStr.length() - 1);
    text.set(textStr);
  }
}

void ScreenInput::unset() {
  textStr = "";
  text.unset();
  titleText.unset();
}
