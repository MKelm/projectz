#include "main.hpp"

Main::Main(Uint8 m_maxFPS, Uint8 m_mode, Uint8 m_subMode) {
  maxFPS = m_maxFPS;
  mode = m_mode;
  subMode = m_subMode;

  map.set();
  map.load();

  screen.init(640, 480, 32, mode);
  screen.initMap(&map);

  events.init();
}

void Main::loop() {
  Uint32 frameStart = 0;
  bool quit = false;
  while (quit == false) {
    frameStart = SDL_GetTicks();

    Uint8 eventSignal = events.handle(mode, subMode);
    switch (eventSignal) {
      // general
      case EVENT_RESIZE:
        screen.resize(events.getLastWidth(), events.getLastHeight());
        break;
      case EVENT_QUIT:
        quit = true;
        break;
      // editor
      case EVENT_EDITOR_TOGGLE_SUB_MODE:
        subMode = (subMode == SUB_MODE_EDITOR_MAP) ?
          SUB_MODE_EDITOR_LIST : SUB_MODE_EDITOR_MAP;
        break;
      // editor map
      case EVENT_EDITOR_MAP_TOGGLE_GRID:
        screen.map.toggleGrid();
        break;
      case EVENT_EDITOR_MAP_INCREASE_SIZE:
        map.increaseSize(1);
        screen.map.resetFieldSelection();
        screen.map.updateSize();
        screen.updateFooterText();
        break;
      case EVENT_EDITOR_MAP_DECREASE_SIZE:
        map.decreaseSize(1);
        screen.map.resetFieldSelection();
        screen.map.updateSize();
        screen.updateFooterText();
        break;
      case EVENT_EDITOR_MAP_FIELD_SELECTION:
        screen.map.selectField(events.getLastPosX(), events.getLastPosY());
        break;
      case EVENT_EDITOR_MAP_MOVE_START:
        screen.map.moveSet(events.getLastPosX(), events.getLastPosY());
        break;
      case EVENT_EDITOR_MAP_MOVE_END:
        screen.map.resetMove();
        break;
    }

    screen.update();

    if ((SDL_GetTicks() - frameStart) < (1000 / maxFPS)) {
      SDL_Delay((1000 / maxFPS) - (SDL_GetTicks() - frameStart));
    }
  }
}

void Main::quit() {
  map.save();
  map.unset();
  screen.quit();
}
