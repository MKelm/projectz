#include "surface.hpp"

int Surface::getWidth() {
  return surface->w;
}

int Surface::getHeight() {
  return surface->h;
}

void Surface::set(SDL_Surface *p_surface) {
  surface = p_surface;
}

SDL_Surface *Surface::get() {
  return surface;
}

void Surface::apply(Uint16 x, Uint16 y, SDL_Surface* source) {
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(source, NULL, surface, &offset);
}

void Surface::unset() {
  free(surface);
}
