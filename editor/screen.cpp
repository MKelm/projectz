#include "global.hpp"
#include "screen.hpp"

Screen::Screen(int s_width, int s_height, int s_bpp, string s_title) {
  width = s_width;
  height = s_height;
  bpp = s_bpp;
  update = false;
  title = s_title;
  footer = "";

  SDL_Init(SDL_INIT_EVERYTHING);
  surface = SDL_SetVideoMode(
    width, height, bpp, SDL_SWSURFACE | SDL_RESIZABLE
  );
  SDL_WM_SetCaption(title.c_str(), NULL);
}

Screen::~Screen() {
  SDL_Quit();
}
