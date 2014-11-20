#include "views.hpp"

// VIEW
void View::event(SDL_Event *event) {
  // handle input
}
void View::update() {
  SDL_Flip(screen);
}

// MAP VIEW
void MapView::update() {
  SDL_FillRect(
    screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0)
  );
  View::update();
}
