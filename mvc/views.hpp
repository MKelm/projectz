#ifndef _INCLUDE_VIEWS_HPP
#define _INCLUDE_VIEWS_HPP

#include "global.hpp"
#include "models.hpp"

class View {
  public:
    Model *model;
    SDL_Surface *screen;
    virtual void addBg(Uint8, Uint8, Uint8);
    virtual void event(SDL_Event *);
    virtual void update();
    virtual ~View() {};
};

class MapView: public View {
  public:
    void update();
};

#endif
