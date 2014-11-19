#ifndef _INCLUDE_SURFACE_HPP
#define _INCLUDE_SURFACE_HPP

#include "global.hpp"

class Surface {
  protected:
    Uint16 width;
    Uint16 height;
    Uint8 bpp;
    SDL_Surface *surface;
  public:
    void setProperties(Uint16, Uint16, Uint8);
    int getWidth();
    int getHeight();
    void apply(Uint16, Uint16, SDL_Surface*);
    void applyDest(Uint16, Uint16, SDL_Surface*, SDL_Surface*);
    void applyFrame(Uint16, Uint16, SDL_Surface*, SDL_Rect);
    void set(SDL_Surface*);
    SDL_Surface *get();
    SDL_Surface *loadImage(string);
    void unset();
};

#endif
