#include "global.hpp"
#include "screen.hpp"

Screen::Screen(int s_width, int s_height, int s_bpp, int s_mode) {
  width = s_width;
  height = s_height;
  bpp = s_bpp;
  mode = s_mode;
  doUpdate = true;

  string header = "Project Z";
  string footer = "";
  if (mode == MODE_EDITOR) {
    header = header + " - Editor";
    footer = "0/0";
  }

  cout << "Set SDL" << endl;
  SDL_Init(SDL_INIT_EVERYTHING);

  cout << "Set Screen" << endl;
  // SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE
  surface = SDL_SetVideoMode(
    width, height, bpp, SDL_SWSURFACE | SDL_RESIZABLE
  );
  SDL_WM_SetCaption(header.c_str(), NULL);

  headerText.initTTF();
  headerText.set(header);
  footerText.set(footer);

  if (doUpdate == true)
    update();

  SDL_Delay(2000); // todo remove later
}

void Screen::applySurface(int x, int y, SDL_Surface* source) {
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
  doUpdate = false;
}

void Screen::quit() {
  headerText.unset();
  footerText.unset();
  headerText.quitTTF();
  cout << "Unset SDL" << endl;
  SDL_Quit();
}
