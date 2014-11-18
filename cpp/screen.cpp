#include "screen.hpp"

void Screen::init(Uint16 pWidth, Uint16 pHeight, Uint8 pBpp, Uint8 pMode, Uint8 pSubMode) {
  bpp = pBpp;
  mode = pMode;
  subMode = pSubMode;

  string windowTitleStr = "Project Z";
  string footerLeftStr = "idx.CodeLab 2014";
  string footerRightStr = "";
  if (mode == MODE_EDITOR) {
    windowTitleStr = windowTitleStr + " - Editor";
    footerRightStr = "0/0";
  }

  #ifdef DEBUG
    cout << "Set SDL" << endl;
  #endif
  SDL_Init(SDL_INIT_EVERYTHING);

  #ifdef DEBUG
    cout << "Set Screen" << endl;
  #endif

  resize(pWidth, pHeight);
  SDL_WM_SetCaption(windowTitleStr.c_str(), NULL);

  footerLeftText.initTTF();
  footerLeftText.set(footerLeftStr);
  footerRightText.set(footerRightStr);

  list.set(surface);
  if (mode == MODE_EDITOR) {
    list.init(LIST_MODE_EDITOR_TERRAIN);
  } else if (mode == MODE_GAME) {
    // no game lists currently
  }
}

void Screen::setSubMode(Uint8 pSubMode) {
  subMode = pSubMode;
}

void Screen::initMap(Map *pMap) {
  map.init(pMap, (mode == MODE_EDITOR) ? true : false);
  map.set(surface);
  updateFooterRightText();
}

void Screen::updateFooterRightText() {
  if (mode == MODE_EDITOR) {
    footerRightText.set(map.getSizeString());
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
  if (subMode == SUB_MODE_EDITOR_MAP || subMode == SUB_MODE_GAME_MAP) {
    map.show();
    map.showGrid();
    map.showFieldSelection();
  } else if (subMode == SUB_MODE_EDITOR_LIST) {
    list.show();
  }
  apply(0, height - footerLeftText.getHeight(), footerLeftText.get());
  apply(
    width - footerRightText.getWidth(), height - footerRightText.getHeight(),
    footerRightText.get()
  );
  SDL_Flip(surface);
}

void Screen::quit() {
  map.unset();
  list.unset();
  footerLeftText.unset();
  footerRightText.unset();
  footerLeftText.quitTTF();
  #ifdef DEBUG
    cout << "Unset SDL" << endl;
  #endif
  SDL_Quit();
}
