#ifndef _INCLUDE_EVENTS_HPP
#define _INCLUDE_EVENTS_HPP

#include "global.hpp"

enum {
  EVENT_NONE, // general events
  EVENT_QUIT,
  EVENT_EDITOR_TOGGLE_SUB_MODE, // editor events
  EVENT_EDITOR_MAP_TOGGLE_GRID, // editor map events
  EVENT_EDITOR_MAP_INCREASE_SIZE,
  EVENT_EDITOR_MAP_DECREASE_SIZE,
  EVENT_EDITOR_MAP_LOAD,
  EVENT_EDITOR_MAP_SAVE,
  EVENT_EDITOR_MAP_FIELD_SELECTION,
  EVENT_EDITOR_MAP_MOVE_START,
  EVENT_EDITOR_MAP_MOVE_END,
  EVENT_EDITOR_LIST_SWITCH_TERRAIN, // editor list events
  EVENT_EDITOR_LIST_SWITCH_ITEMS,
  EVENT_EDITOR_LIST_SELECT_ENTRY,
  EVENT_EDITOR_LIST_MOVE_SLIDER,
  EVENT_EDITOR_LIST_WHEELUP,
  EVENT_EDITOR_LIST_WHEELDOWN
};

class Events {
    SDL_Event event;
    bool rMouseBtn;
    bool lMouseBtn;
    Uint16 posX;
    Uint16 posY;
  public:
    Uint16 getPosX();
    Uint16 getPosY();
    Uint8 handle(Uint8, Uint8);
    Uint8 handleEditorMap();
    Uint8 handleEditorList();
};

#endif
