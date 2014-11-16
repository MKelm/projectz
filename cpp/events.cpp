#include "events.hpp"

Uint8 Events::handle(Uint8 mode) {
  Uint8 eventSignal = EVENT_NONE;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE: eventSignal = EVENT_QUIT; break;
        default: ;
      }
      switch (mode) {
        case MODE_EDITOR:
          break;
        case MODE_GAME:
          break;
      }
    }
    if (event.type == SDL_QUIT) {
      eventSignal = EVENT_QUIT;
    }
  }
  return eventSignal;
}
