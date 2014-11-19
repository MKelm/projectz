#include "main.hpp"

Main::Main(Uint8 pMaxFPS, Uint8 pMode, Uint8 pSubMode) {
  hasQuitStatus = false;
  maxFPS = pMaxFPS;
  mode = pMode;
  subMode = pSubMode;

  Uint16 width = 640;
  Uint16 height = 480;
  Uint8 bpp = 32;

  lists.load();

  map.setNames(&lists);
  map.load();

  screen.init(width, height, bpp, mode, subMode);
  screen.initMap(&map);

  screen.list.setEntries(&lists);

  eventHandler.init(&event);
}

void Main::handleGeneralEventSignal(Uint8 eventSignal) {
  switch (eventSignal) {
    // general
    case EVENT_RESIZE:
      screen.resize(
        eventHandler.getLastWidth(), eventHandler.getLastHeight(), false
      );
      break;
    case EVENT_QUIT:
      hasQuitStatus = true;
      break;
  }
}

void Main::handleEditorEventSignal(Uint8 eventSignal) {
  switch (eventSignal) {
    // editor
    case EVENT_EDITOR_TOGGLE_SUB_MODE:
      subMode = (subMode == SUB_MODE_EDITOR_MAP) ?
        SUB_MODE_EDITOR_LIST : SUB_MODE_EDITOR_MAP;
      screen.setSubMode(subMode);
      break;
    // editor map
    case EVENT_EDITOR_MAP_TOGGLE_GRID:
      screen.map.toggleGrid();
      break;
    case EVENT_EDITOR_MAP_INCREASE_SIZE:
      map.increaseSize(1);
      screen.map.resetFieldSelection();
      screen.map.updateSize();
      screen.updateFooterRightText();
      break;
    case EVENT_EDITOR_MAP_DECREASE_SIZE:
      map.decreaseSize(1);
      screen.map.resetFieldSelection();
      screen.map.updateSize();
      screen.updateFooterRightText();
      break;
    case EVENT_EDITOR_MAP_FIELD_SELECTION:
      if (screen.map.selectField(
            eventHandler.getLastPosX(), eventHandler.getLastPosY()
          ) == true) {
        map.setField(
          screen.map.getFieldSelectionColumn(), screen.map.getFieldSelectionRow(),
          screen.list.getSelectedIdx(),
          screen.list.getMode() == LIST_MODE_EDITOR_TERRAIN ? "terrain" : "item"
        );
      }
      break;
    case EVENT_EDITOR_MAP_MOVE_START:
      screen.map.moveSet(
        eventHandler.getLastPosX(), eventHandler.getLastPosY()
      );
      break;
    case EVENT_EDITOR_MAP_MOVE_END:
      screen.map.resetMove();
      break;
    case EVENT_EDITOR_MAP_SET_RESOURCE:
      if (screen.map.getFieldSelectionColumn() > -1 &&
          screen.map.getFieldSelectionRow() > -1) {
        if (map.fieldHasItem(screen.map.getFieldSelectionColumn(),
              screen.map.getFieldSelectionRow()) == true) {
          subMode = (subMode == SUB_MODE_EDITOR_MAP) ?
            SUB_MODE_EDITOR_MAP_INPUT : SUB_MODE_EDITOR_MAP;
          screen.setSubMode(subMode);

          if (subMode == SUB_MODE_EDITOR_MAP) {
            map.setField(
              screen.map.getFieldSelectionColumn(),
              screen.map.getFieldSelectionRow(),
              stoi(screen.input.getTextStr()),
              "resource"
            );
          } else {
            screen.input.setTextStr(
              to_string(
                map.getField(
                  screen.map.getFieldSelectionRow(),
                  screen.map.getFieldSelectionColumn(),
                  "resource"
                )
              )
            );
          }
        }
      }
      break;
    case EVENT_EDITOR_MAP_INPUT_APPEND_CHAR:
      if (subMode == SUB_MODE_EDITOR_MAP_INPUT) {
        screen.input.appendChar(eventHandler.getInputStr());
      }
      break;
    case EVENT_EDITOR_MAP_INPUT_REMOVE_CHAR:
      if (subMode == SUB_MODE_EDITOR_MAP_INPUT) {
        screen.input.removeChar();
      }
      break;
    // editor list
    case EVENT_EDITOR_LIST_SWITCH_TERRAIN:
      screen.list.unset();
      screen.list.init(LIST_MODE_EDITOR_TERRAIN);
      screen.list.setEntries(&lists);
      break;
    case EVENT_EDITOR_LIST_SWITCH_ITEMS:
      screen.list.unset();
      screen.list.init(LIST_MODE_EDITOR_ITEMS);
      screen.list.setEntries(&lists);
      break;
    case EVENT_EDITOR_LIST_SELECT_ENTRY:
      if (screen.list.sliderActive(
            eventHandler.getLastPosX(), eventHandler.getLastPosY()
          ) == false)
        screen.list.selectEntry(eventHandler.getLastPosY());
      break;
    case EVENT_EDITOR_LIST_MOVE_SLIDER:
      if (screen.list.sliderActive(
            eventHandler.getLastPosX(), eventHandler.getLastPosY()
          ) == true)
        screen.list.moveSlider(eventHandler.getLastPosY());
      break;
    case EVENT_EDITOR_LIST_WHEELUP:
      screen.list.scroll(true, 10.f);
      break;
    case EVENT_EDITOR_LIST_WHEELDOWN:
      screen.list.scroll(false, 10.f);
      break;
  }
}

void Main::handleGameEventSignal(Uint8 eventSignal) {
  switch (eventSignal) {
    // game
    case EVENT_GAME_TOGGLE_SUB_MODE:
      subMode = (subMode == SUB_MODE_GAME_MAP) ?
        SUB_MODE_GAME_LIST : SUB_MODE_GAME_MAP;
      screen.setSubMode(subMode);
      break;
    // game map
    case EVENT_GAME_MAP_FIELD_SELECTION:
      screen.map.selectField(
        eventHandler.getLastPosX(), eventHandler.getLastPosY()
      );
      break;
    case EVENT_GAME_MAP_MOVE_START:
      screen.map.moveSet(
        eventHandler.getLastPosX(), eventHandler.getLastPosY()
      );
      break;
    case EVENT_GAME_MAP_MOVE_END:
      screen.map.resetMove();
      break;
    // buildings list
    case EVENT_GAME_LIST_SELECT_ENTRY:
      if (screen.list.sliderActive(
            eventHandler.getLastPosX(), eventHandler.getLastPosY()
          ) == false)
        screen.list.selectEntry(eventHandler.getLastPosY());
      break;
    case EVENT_GAME_LIST_MOVE_SLIDER:
      if (screen.list.sliderActive(
            eventHandler.getLastPosX(), eventHandler.getLastPosY()
          ) == true)
        screen.list.moveSlider(eventHandler.getLastPosY());
      break;
    case EVENT_GAME_LIST_WHEELUP:
      screen.list.scroll(true, 10.f);
      break;
    case EVENT_GAME_LIST_WHEELDOWN:
      screen.list.scroll(false, 10.f);
      break;
  }
}

void Main::loop() {
  Uint32 frameStart = 0;
  Uint8 eventSignal;
  while (hasQuitStatus == false) {
    frameStart = SDL_GetTicks();

    eventSignal = EVENT_NONE;
    while (SDL_PollEvent(&event)) {
      eventSignal = eventHandler.getSignal(mode, subMode);
      handleGeneralEventSignal(eventSignal);
      switch (mode) {
        case MODE_EDITOR:
          handleEditorEventSignal(eventSignal);
          break;
        case MODE_GAME:
          handleGameEventSignal(eventSignal);
          break;
      }
    }
    screen.update();

    if ((SDL_GetTicks() - frameStart) < (1000 / maxFPS)) {
      SDL_Delay((1000 / maxFPS) - (SDL_GetTicks() - frameStart));
    }
  }
}

void Main::quit() {
  if (mode = MODE_EDITOR) {
    map.save();
  }
  map.unset();
  lists.unset();
  screen.quit();
}
