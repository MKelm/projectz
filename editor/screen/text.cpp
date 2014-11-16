#include "../global.hpp"
#include "text.hpp"

bool ScreenText::hasTTF = false;

ScreenText::ScreenText() {
  fontFile = "../fonts/beyourself.ttf";
  fontSize = 24;
  fontColor.r = 255;
  fontColor.g = 255;
  fontColor.b = 255;
  fontColor.a = 255;
}

void ScreenText::initTTF() {
  if (ScreenText::hasTTF != true) {
    TTF_Init();
    ScreenText::hasTTF = true;
    cout << "Set SDL_TTF" << endl;
  }
}

void ScreenText::set(string t_text) {
  cout << "Open font" << endl;
  font = TTF_OpenFont(fontFile.c_str(), fontSize);
  text = t_text;
  SDL_Color tmpFontColor = { fontColor.r, fontColor.g, fontColor.b, fontColor.a };
  surface = TTF_RenderText_Solid(font, text.c_str(), tmpFontColor);
}

int ScreenText::getWidth() {
  return surface->w;
}

int ScreenText::getHeight() {
  return surface->h;
}

SDL_Surface *ScreenText::getSurface() {
  return surface;
}

void ScreenText::unset() {
  text = "";
  cout << "Close font" << endl;
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

void ScreenText::quitTTF() {
  if (ScreenText::hasTTF == true) {
    TTF_Quit();
    ScreenText::hasTTF = false;
    cout << "Unset SDL_TTF" << endl;
  }
}
