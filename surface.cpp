#include "surface.hpp"

int Surface::getWidth() {
  return surface->w;
}

int Surface::getHeight() {
  return surface->h;
}

void Surface::set(SDL_Surface *pSurface) {
  surface = pSurface;
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

SDL_Surface *Surface::loadImage(string file) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load(file.c_str());
  #ifdef DEBUG
    cout << "try to load image " << file << endl;
  #endif
  if (loadedImage != NULL) {
    #ifdef DEBUG
      cout << "loaded image " << file << endl;
    #endif
    optimizedImage = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    if (optimizedImage != NULL) {
      SDL_SetColorKey(
        optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0, 0)
      );
    }
  }
  return optimizedImage;
}

void Surface::unset() {
  free(surface);
}