#include "main.hpp"

Main::Main(Uint8 m_maxFPS, Uint8 m_mode, Uint8 m_subMode) {
  maxFPS = m_maxFPS;
  mode = m_mode;
  subMode = m_subMode;

  map.set();
  map.load();

  screen.init(640, 480, 32, mode);
  screen.initMap(map);
}

void Main::loop() {
  Uint32 frameStart = 0;
  bool quit = false;
  while (quit == false) {
    frameStart = SDL_GetTicks();

    Uint8 eventSignal = events.handle(mode, subMode);
    if (eventSignal == EVENT_EDITOR_TOGGLE_SUB_MODE) {
      subMode = (subMode == SUB_MODE_EDITOR_MAP) ?
        SUB_MODE_EDITOR_LIST : SUB_MODE_EDITOR_MAP;
    }
    if (eventSignal == EVENT_RESIZE) {
      screen.resize(events.getLastWidth(), events.getLastHeight());
    }
    if (eventSignal == EVENT_QUIT) {
      quit = true;
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
