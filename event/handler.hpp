#ifndef _INCLUDE_EVENT_HANDLER_HPP
#define _INCLUDE_EVENT_HANDLER_HPP

#include "../global.hpp"

enum {
  EVENT_NONE, // general events
  EVENT_QUIT,
  EVENT_RESIZE,
  EVENT_EDITOR_TOGGLE_SUB_MODE, // editor events
  EVENT_EDITOR_MAP_TOGGLE_GRID, // editor map events
  EVENT_EDITOR_MAP_INCREASE_SIZE,
  EVENT_EDITOR_MAP_DECREASE_SIZE,
  EVENT_EDITOR_MAP_LOAD,
  EVENT_EDITOR_MAP_SAVE,
  EVENT_EDITOR_MAP_FIELD_SELECTION,
  EVENT_EDITOR_MAP_MOVE_START,
  EVENT_EDITOR_MAP_MOVE_END,
  EVENT_EDITOR_MAP_SET_RESOURCE,
  EVENT_EDITOR_MAP_INPUT_APPEND_CHAR,
  EVENT_EDITOR_MAP_INPUT_REMOVE_CHAR,
  EVENT_EDITOR_LIST_SWITCH_TERRAIN, // editor list events
  EVENT_EDITOR_LIST_SWITCH_ITEMS,
  EVENT_EDITOR_LIST_SELECT_ENTRY,
  EVENT_EDITOR_LIST_MOVE_SLIDER,
  EVENT_EDITOR_LIST_WHEELUP,
  EVENT_EDITOR_LIST_WHEELDOWN,
  EVENT_GAME_MAP_FIELD_SELECTION, // game map events
  EVENT_GAME_MAP_MOVE_START,
  EVENT_GAME_MAP_MOVE_END
};

class EventHandler {
    SDL_Event *event;
    bool rMouseBtn;
    bool lMouseBtn;
    Uint16 lastPosX;
    Uint16 lastPosY;
    Uint16 lastWidth;
    Uint16 lastHeight;
    string inputStr;
  public:
    void init(SDL_Event *);
    Uint16 getLastPosX();
    Uint16 getLastPosY();
    Uint16 getLastWidth();
    Uint16 getLastHeight();
    Uint8 getSignal(Uint8, Uint8);
    Uint8 getEditorMapSignal(Uint8);
    Uint8 getEditorListSignal();
    Uint8 getGameMapSignal();
    string getInputStr();
};

#endif
