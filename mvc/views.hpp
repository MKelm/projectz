#ifndef _INCLUDE_VIEWS_HPP
#define _INCLUDE_VIEWS_HPP

#include "global.hpp"

class View {
  public:
    SDL_Surface *screen;
    void event(SDL_Event *);
    void update();
    virtual ~View() {};
};

class MapView: public View {
  public:
    void update();
};

#endif
