#include "global.hpp"
#include "models.hpp"
#include "views.hpp"
#include "controllers.hpp"

class ProjectZ {
    bool run;
    Uint8 mode;
    SDL_Surface *screen;
    Controller *controller;
  public:
    ProjectZ(Uint8);
    void loop();
    ~ProjectZ();
};
ProjectZ::ProjectZ(Uint8 argMode) {
  run = true;
  mode = argMode;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_EnableUNICODE(SDL_ENABLE);
  screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_RESIZABLE);

  controller = new MapController();
  controller->view->screen = screen;
}
void ProjectZ::loop() {
  Uint32 frameStart = 0;
  Uint16 maxFPS = 30;
  SDL_Event event;
  while (run == true) {
    frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
      controller->event(&event);
      if (event.type == SDL_QUIT) {
        run = false;
      }
    }
    controller->update();

    if ((SDL_GetTicks() - frameStart) < (1000 / maxFPS)) {
      SDL_Delay((1000 / maxFPS) - (SDL_GetTicks() - frameStart));
    }
  }
}
ProjectZ::~ProjectZ() {
  delete controller;
  SDL_EnableUNICODE(SDL_DISABLE);
  SDL_Quit();
}

int main(int argc, char* argv[]) {
  Uint8 mode = MODE_GAME;
  if (argc > 1) {
    string argMode = argv[1];
    if (argMode == "--editor")
      mode = MODE_EDITOR;
  }
  ProjectZ *projectZ = new ProjectZ(mode);
  projectZ->loop();
  delete projectZ;
}
