#ifndef _INCLUDE_CONTROLLERS_HPP
#define _INCLUDE_CONTROLLERS_HPP

#include "global.hpp"
#include "models.hpp"
#include "views.hpp"

class Controller {
  public:
    Model *model;
    View *view;
    void event(SDL_Event *);
    void update();
    virtual ~Controller();
};

class MapController: public Controller {
  public:
    MapController();
};

#endif
