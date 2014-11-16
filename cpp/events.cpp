#include "events.hpp"

Uint16 Events::getPosX() {
  return posX;
}

Uint16 Events::getPosY() {
  return posY;
}

Uint8 Events::handleEditorMap() {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_g: return EVENT_EDITOR_MAP_TOGGLE_GRID; break;
      case SDLK_PLUS: return EVENT_EDITOR_MAP_INCREASE_SIZE; break;
      case SDLK_MINUS: return EVENT_EDITOR_MAP_DECREASE_SIZE; break;
      case SDLK_l: return EVENT_EDITOR_MAP_LOAD; break;
      case SDLK_s: return EVENT_EDITOR_MAP_SAVE; break;
      default: ;
    }
  }
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
  if (event.type == SDL_MOUSEMOTION) {
    if (lMouseBtn == true) {
      posX = event.button.x;
      posY = event.button.y;
      return EVENT_EDITOR_MAP_FIELD_SELECTION;
    } else if (rMouseBtn == true) {
      posX = event.button.x;
      posY = event.button.y;
      return EVENT_EDITOR_MAP_MOVE_START;
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
  return EVENT_NONE;
}

Uint8 Events::handleEditorList() {
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_1: return EVENT_EDITOR_LIST_SWITCH_TERRAIN; break;
      case SDLK_2: return EVENT_EDITOR_LIST_SWITCH_ITEMS; break;
      default: ;
    }
  }
  if (event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_LEFT) {
    lMouseBtn = true;
    posX = event.button.x;
    posY = event.button.y;
    return EVENT_EDITOR_LIST_SELECT_ENTRY;
  }
  if (event.type == SDL_MOUSEMOTION && lMouseBtn == true) {
    posX = event.motion.x;
    posY = event.motion.y;
    return EVENT_EDITOR_LIST_MOVE_SLIDER;
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_WHEELUP) {
      return EVENT_EDITOR_LIST_WHEELUP;
    } else if (event.button.button == SDL_BUTTON_WHEELDOWN) {
      return EVENT_EDITOR_LIST_WHEELDOWN;
    } else {
      lMouseBtn = false;
    }
  }
  return EVENT_NONE;
}

Uint8 Events::handle(Uint8 mode, Uint8 subMode) {
  Uint8 eventSignal = EVENT_NONE;
  while (SDL_PollEvent(&event)) {

    switch (mode) {
      case MODE_EDITOR:
        if (subMode == SUB_MODE_EDITOR_MAP) {
          eventSignal = handleEditorMap();
        } else if (subMode == SUB_MODE_EDITOR_LIST) {
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
