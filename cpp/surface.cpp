#include "surface.hpp"

int Surface::getWidth() {
  return surface->w;
}

int Surface::getHeight() {
  return surface->h;
}

SDL_Surface *Surface::getSurface() {
  return surface;
}

void Surface::applySurface(Uint16 x, Uint16 y, SDL_Surface* source) {
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;
  SDL_BlitSurface(source, NULL, surface, &offset);
}

void Surface::unset() {
  free(surface);
}
