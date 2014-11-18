#ifndef _INCLUDE_SURFACE_HPP
#define _INCLUDE_SURFACE_HPP

#include "global.hpp"

class Surface {
  protected:
    SDL_Surface *surface;
  public:
    int getWidth();
    int getHeight();
    SDL_Surface *getSurface();
    void applySurface(Uint16, Uint16, SDL_Surface*);
    void unset();
};

#endif
