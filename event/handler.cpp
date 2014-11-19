#include "handler.hpp"

void EventHandler::init(SDL_Event *pEvent) {
  rMouseBtn = false;
  lMouseBtn = false;
  lastPosX = 0;
  lastPosY = 0;
  event = pEvent;
  inputStr = "";
}

Uint16 EventHandler::getLastPosX() {
  return lastPosX;
}

Uint16 EventHandler::getLastPosY() {
  return lastPosY;
}

Uint16 EventHandler::getLastWidth() {
  return lastWidth;
}

Uint16 EventHandler::getLastHeight() {
  return lastHeight;
}

string EventHandler::getInputStr() {
  return inputStr;
}

Uint8 EventHandler::getEditorMapSignal(Uint8 subMode) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_g: return EVENT_EDITOR_MAP_TOGGLE_GRID; break;
      case SDLK_PLUS: return EVENT_EDITOR_MAP_INCREASE_SIZE; break;
      case SDLK_MINUS: return EVENT_EDITOR_MAP_DECREASE_SIZE; break;
      case SDLK_l: return EVENT_EDITOR_MAP_LOAD; break;
      case SDLK_s: return EVENT_EDITOR_MAP_SAVE; break;
      case SDLK_r: return EVENT_EDITOR_MAP_SET_RESOURCE; break;
      case SDLK_TAB: return EVENT_EDITOR_TOGGLE_SUB_MODE; break;
      default: ;
    }

    if (subMode == SUB_MODE_EDITOR_MAP_INPUT) {
      inputStr = "";
      if (event->key.keysym.unicode >= (Uint16)'0' &&
          event->key.keysym.unicode <= (Uint16)'9') {
        char inputCStr[4];
        sprintf(inputCStr, "%c", event->key.keysym.unicode);
        inputStr = inputCStr;
        return EVENT_EDITOR_MAP_INPUT_APPEND_CHAR;
      } else if (event->key.keysym.sym == SDLK_BACKSPACE) {
        return EVENT_EDITOR_MAP_INPUT_REMOVE_CHAR;
      }
    }

  }
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.button == SDL_BUTTON_RIGHT) {
      rMouseBtn = true;
    } else if (event->button.button == SDL_BUTTON_LEFT) {
      lMouseBtn = true;
      lastPosX = event->button.x;
      lastPosY = event->button.y;
      return EVENT_EDITOR_MAP_FIELD_SELECTION;
    }
  }
  if (event->type == SDL_MOUSEBUTTONUP) {
    if (event->button.button == SDL_BUTTON_RIGHT) {
      rMouseBtn = false;
      return EVENT_EDITOR_MAP_MOVE_END;
    } else if (event->button.button == SDL_BUTTON_LEFT) {
      lMouseBtn = false;
    }
  }
  if (event->type == SDL_MOUSEMOTION) {
    if (lMouseBtn == true) {
      lastPosX = event->button.x;
      lastPosY = event->button.y;
      return EVENT_EDITOR_MAP_FIELD_SELECTION;
    } else if (rMouseBtn == true) {
      lastPosX = event->button.x;
      lastPosY = event->button.y;
      return EVENT_EDITOR_MAP_MOVE_START;
    }
  }
  return EVENT_NONE;
}

Uint8 EventHandler::getEditorListSignal() {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_1: return EVENT_EDITOR_LIST_SWITCH_TERRAIN; break;
      case SDLK_2: return EVENT_EDITOR_LIST_SWITCH_ITEMS; break;
      case SDLK_TAB: return EVENT_EDITOR_TOGGLE_SUB_MODE; break;
      default: ;
    }
  }
  if (event->type == SDL_MOUSEBUTTONDOWN &&
      event->button.button == SDL_BUTTON_LEFT) {
    lMouseBtn = true;
    lastPosX = event->button.x;
    lastPosY = event->button.y;
    return EVENT_EDITOR_LIST_SELECT_ENTRY;
  }
  if (event->type == SDL_MOUSEBUTTONUP) {
    if (event->button.button == SDL_BUTTON_WHEELUP) {
      return EVENT_EDITOR_LIST_WHEELUP;
    } else if (event->button.button == SDL_BUTTON_WHEELDOWN) {
      return EVENT_EDITOR_LIST_WHEELDOWN;
    } else {
      lMouseBtn = false;
    }
  }
  if (event->type == SDL_MOUSEMOTION && lMouseBtn == true) {
    lastPosX = event->motion.x;
    lastPosY = event->motion.y;
    return EVENT_EDITOR_LIST_MOVE_SLIDER;
  }
  return EVENT_NONE;
}

Uint8 EventHandler::getSignal(Uint8 mode, Uint8 subMode) {
  lastPosX = 0;
  lastPosY = 0;
  Uint8 eventSignal = EVENT_NONE;

  switch (mode) {
    case MODE_EDITOR:
      if (subMode == SUB_MODE_EDITOR_MAP || subMode == SUB_MODE_EDITOR_MAP_INPUT) {
        eventSignal = getEditorMapSignal(subMode);
      } else if (subMode == SUB_MODE_EDITOR_LIST) {
        eventSignal = getEditorListSignal();
      }
      break;
    case MODE_GAME:
      // todo...
      break;
  }

  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
      case SDLK_ESCAPE: eventSignal = EVENT_QUIT; break;
      default: ;
    }
  }
  if (event->type == SDL_VIDEORESIZE) {
    lastWidth = event->resize.w;
    lastHeight = event->resize.h;
    eventSignal = EVENT_RESIZE;
  }
  if (event->type == SDL_QUIT) {
    eventSignal = EVENT_QUIT;
  }

  return eventSignal;
}
