#include "main.hpp"

Main::Main(Uint8 m_maxFPS, Uint8 m_mode) {
  maxFPS = m_maxFPS;
  mode = m_mode;
  screen.init(640, 480, 32, mode);
}

void Main::loop() {
  Uint32 frameStart = 0;
  bool quit = false;
  while (quit == false) {
    frameStart = SDL_GetTicks();

    Uint8 eventSignal = events.handle(mode, MODE_EDITOR_MAP);
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
  screen.quit();
}
