#include "../global.hpp"
#include "text.hpp"

bool ScreenText::hasTTF = false;

ScreenText::ScreenText() {
  fontFile = "fonts/beyourself.ttf";
}

void ScreenText::set(string t_text) {
  if (ScreenText::hasTTF != true) {
    TTF_Init();
    ScreenText::hasTTF = true;
    cout << "Set SDL_TTF" << endl;
  }
  text = t_text;
}

void ScreenText::unset() {
  if (ScreenText::hasTTF == true) {
    TTF_Quit();
    ScreenText::hasTTF = false;
    cout << "Unset SDL_TTF" << endl;
  }
}
