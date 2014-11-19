#include "text.hpp"

bool ScreenText::hasTTF = false;

ScreenText::ScreenText() {
  fontFile = "../fonts/beyourself.ttf";
  fontSize = 24;
  fontColor.r = 255;
  fontColor.g = 255;
  fontColor.b = 255;
  fontColor.a = 255;
  hasText = false;
}

void ScreenText::setFontFile(string pFontFile) {
  fontFile = pFontFile;
}

void ScreenText::setFontSize(Uint8 pFontSize) {
  fontSize = pFontSize;
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

void ScreenText::set(string pText) {
  if (hasText == true)
    unset();
  #ifdef DEBUG
    cout << "Open font" << endl;
  #endif
  font = TTF_OpenFont(fontFile.c_str(), fontSize);
  text = pText;
  SDL_Color tmpFontColor = { fontColor.r, fontColor.g, fontColor.b, fontColor.a };
  surface = TTF_RenderText_Solid(font, text.c_str(), tmpFontColor);
  hasText = true;
}

void ScreenText::unset() {
  text = "";
  #ifdef DEBUG
    cout << "Close font" << endl;
  #endif
  Surface::unset();
  TTF_CloseFont(font);
  hasText = false;
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
