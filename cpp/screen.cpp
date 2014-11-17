#include "screen.hpp"

void Screen::init(Uint16 s_width, Uint16 s_height, Uint8 s_bpp, Uint8 s_mode) {
  bpp = s_bpp;
  mode = s_mode;

  string header = "Project Z";
  string footer = "idx.CodeLab 2014";
  if (mode == MODE_EDITOR) {
    header = header + " - Editor";
    footer = "0/0";
  }

  #ifdef DEBUG
    cout << "Set SDL" << endl;
  #endif
  SDL_Init(SDL_INIT_EVERYTHING);

  #ifdef DEBUG
    cout << "Set Screen" << endl;
  #endif

  resize(s_width, s_height);
  SDL_WM_SetCaption(header.c_str(), NULL);

  headerText.initTTF();
  headerText.set(header);
  footerText.set(footer);
}

void Screen::resize(Uint16 s_width, Uint16 s_height) {
  width = s_width;
  height = s_height;
  // SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE
  surface = SDL_SetVideoMode(
    width, height, bpp, SDL_SWSURFACE | SDL_RESIZABLE
  );
}

void Screen::applySurface(Uint16 x, Uint16 y, SDL_Surface* source) {
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(source, NULL, surface, &offset);
}

void Screen::update() {
  SDL_FillRect(
    surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0, 0, 0)
  );
  applySurface(0, 0, headerText.getSurface());
  applySurface(
    width - footerText.getWidth(), height - footerText.getHeight(),
    footerText.getSurface()
  );
  SDL_Flip(surface);
}

void Screen::quit() {
  headerText.unset();
  footerText.unset();
  headerText.quitTTF();
  #ifdef DEBUG
    cout << "Unset SDL" << endl;
  #endif
  SDL_Quit();
}
