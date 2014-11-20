#include "views.hpp"

// VIEW
void View::event(SDL_Event *event) {
  // handle input
}
void View::update() {
  cout << "view update" << endl;
  SDL_Flip(screen);
}
void View::addBg(Uint8 r, Uint8 g, Uint8 b) {
  SDL_FillRect(
    screen, &screen->clip_rect, SDL_MapRGB(screen->format, r, g, b)
  );
}

// MAP VIEW
void MapView::update() {
  cout << "map view update" << endl;
  addBg(0, 0, 255);
  View::update();
}
