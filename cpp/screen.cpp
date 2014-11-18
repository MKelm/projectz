#include "screen.hpp"

void Screen::init(Uint16 pWidth, Uint16 pHeight, Uint8 pBpp, Uint8 pMode) {
  bpp = pBpp;
  mode = pMode;

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

  resize(pWidth, pHeight);
  SDL_WM_SetCaption(header.c_str(), NULL);

  headerText.initTTF();
  headerText.set(header);
  footerText.set(footer);
}

void Screen::initMap(Map *pMap) {
  map.init(pMap, (mode == MODE_EDITOR) ? true : false);
  map.set(surface);
  updateFooterText();
}

void Screen::updateFooterText() {
  if (mode == MODE_EDITOR) {
    footerText.set(map.getSizeString());
  }
}

void Screen::resize(Uint16 s_width, Uint16 s_height) {
  width = s_width;
  height = s_height;
  // SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE
  surface = SDL_SetVideoMode(
    width, height, bpp, SDL_SWSURFACE | SDL_RESIZABLE
  );
}

void Screen::update() {
  SDL_FillRect(
    surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0, 0, 0)
  );
  map.show();
  map.showGrid();
  map.showFieldSelection();
  apply(0, 0, headerText.get());
  apply(
    width - footerText.getWidth(), height - footerText.getHeight(),
    footerText.get()
  );
  SDL_Flip(surface);
}

void Screen::quit() {
  map.unset();
  headerText.unset();
  footerText.unset();
  headerText.quitTTF();
  #ifdef DEBUG
    cout << "Unset SDL" << endl;
  #endif
  SDL_Quit();
}
