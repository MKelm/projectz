#include "events.hpp"

Uint16 Events::getPosX() {
  return posX;
}

Uint16 Events::getPosY() {
  return posY;
}

Uint8 Events::handleEditorMap() {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_RIGHT)
      rMouseBtn = true;
    else if (event.button.button == SDL_BUTTON_LEFT) {
      lMouseBtn = true;
      posX = event.button.x;
      posY = event.button.y;
      return EVENT_EDITOR_MAP_FIELD_SELECTION;
    }
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_RIGHT) {
      rMouseBtn = true;
      return EVENT_EDITOR_MAP_MOVE_END;
    } else if (event.button.button == SDL_BUTTON_LEFT) {
      lMouseBtn = false;
    }
  }
  if (event.type == SDL_MOUSEMOTION) {
    if (rMouseBtn == true) {
      posX = event.button.x;
      posY = event.button.y;
      return EVENT_EDITOR_MAP_MOVE_START;
    } else if (lMouseBtn == true) {
      posX = event.button.x;
      posY = event.button.y;
      return EVENT_EDITOR_MAP_FIELD_SELECTION;
    }
  }
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_g: return EVENT_EDITOR_MAP_TOGGLE_GRID; break;
      case SDLK_PLUS: return EVENT_EDITOR_MAP_INCREASE_SIZE; break;
      case SDLK_MINUS: return EVENT_EDITOR_MAP_DECREASE_SIZE; break;
      case SDLK_l: return EVENT_EDITOR_MAP_LOAD; break;
      case SDLK_s: return EVENT_EDITOR_MAP_SAVE; break;
      default: return EVENT_NONE;
    }
  }
  return EVENT_NONE;
}

Uint8 Events::handleEditorList() {

}

Uint8 Events::handle(Uint8 mode, Uint8 subMode) {
  Uint8 eventSignal = EVENT_NONE;
  while (SDL_PollEvent(&event)) {

    switch (mode) {
      case MODE_EDITOR:
        if (subMode == MODE_EDITOR_MAP) {
          eventSignal = handleEditorMap();
        } else if (subMode == MODE_EDITOR_LIST) {
          //eventSignal = handleEditorList();
        }
        break;
      case MODE_GAME:
        // todo...
        break;
    }

    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE: eventSignal = EVENT_QUIT; break;
        default: ;
      }
    }
    if (event.type == SDL_QUIT) {
      eventSignal = EVENT_QUIT;
    }
  }
  return eventSignal;
}
