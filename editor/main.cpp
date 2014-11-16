#include "main.hpp"

Main::Main(Uint8 m_maxFPS, Uint8 m_mode) {
  maxFPS = m_maxFPS;
  screen.init(640, 480, 32, m_mode);
}

void Main::loop() {
  Uint32 frameStart = 0;
  bool quit = false;
  SDL_Event event;
  while (quit == false) {
    frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE: quit = true; break;
          default: ;
        }
      }
      if (event.type == SDL_QUIT) {
        quit = true;
      }
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
