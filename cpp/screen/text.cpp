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
    #ifdef DEBUG
      cout << "Set SDL_TTF" << endl;
    #endif
  }
}

void ScreenText::set(string t_text) {
  #ifdef DEBUG
    cout << "Open font" << endl;
  #endif
  font = TTF_OpenFont(fontFile.c_str(), fontSize);
  text = t_text;
  SDL_Color tmpFontColor = { fontColor.r, fontColor.g, fontColor.b, fontColor.a };
  surface = TTF_RenderText_Solid(font, text.c_str(), tmpFontColor);
}

void ScreenText::unset() {
  text = "";
  #ifdef DEBUG
    cout << "Close font" << endl;
  #endif
  Surface::unset();
  TTF_CloseFont(font);
}

void ScreenText::quitTTF() {
  if (ScreenText::hasTTF == true) {
    TTF_Quit();
    ScreenText::hasTTF = false;
    #ifdef DEBUG
      cout << "Unset SDL_TTF" << endl;
    #endif
  }
}
