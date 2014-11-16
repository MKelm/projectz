#ifndef _INCLUDE_EVENTS_HPP
#define _INCLUDE_EVENTS_HPP

#include "global.hpp"

enum {
  EVENT_NONE,
  EVENT_QUIT
};

class Events {
    SDL_Event event;
  public:
    Uint8 handle(Uint8 mode);
};

#endif
