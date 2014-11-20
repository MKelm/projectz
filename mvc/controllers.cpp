#include "controllers.hpp"

// CONTROLLER
void Controller::event(SDL_Event *event) {
  view->event(event);
}
void Controller::update() {
  if (model->changed == true) {
    view->update();
    model->changed = false;
  }
}
Controller::~Controller() {
  delete model;
  delete view;
  cout << "controller destructor" << endl;
}

// MAP CONTROLLER
MapController::MapController() {
  model = new MapModel(16, 16);
  view = new MapView();
  cout << "map controller constructor" << endl;
}
