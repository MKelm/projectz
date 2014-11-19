#ifndef _INCLUDE_SURFACE_HPP
#define _INCLUDE_SURFACE_HPP

#include "global.hpp"

class Surface {
  protected:
    SDL_Surface *surface;
  public:
    int getWidth();
    int getHeight();
    void apply(Uint16, Uint16, SDL_Surface*);
    void set(SDL_Surface*);
    SDL_Surface *get();
    SDL_Surface *loadImage(string);
    void unset();
};

#endif
