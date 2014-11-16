#include "global.hpp"
#include "screen.hpp"

Screen::Screen(int s_width, int s_height, int s_bpp, int s_mode) {
  width = s_width;
  height = s_height;
  bpp = s_bpp;
  update = false;

  cout << "Set SDL" << endl;
  SDL_Init(SDL_INIT_EVERYTHING);

  string title = "Project Z";
  if (s_mode == MODE_EDITOR) {
    title = title + " - Editor";
    headerText.set(title);
    footerText.set("0/0");
  } else {
    headerText.set(title);
    footerText.set("");
  }

  surface = SDL_SetVideoMode(
    width, height, bpp, SDL_SWSURFACE | SDL_RESIZABLE
  );
  SDL_WM_SetCaption(title.c_str(), NULL);
  SDL_Delay(2000); // todo remove later
  cout << "Set Screen" << endl;

}

Screen::~Screen() {
  headerText.unset();
  footerText.unset();
  cout << "Unset SDL" << endl;
  SDL_Quit();
}
