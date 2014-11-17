#include "map.hpp"

void ScreenMap::init(Map& p_map) {
  map = p_map;
  imagesSize = 64;

  Uint16 terrainNamesCount = map.getTerrainNamesCount();
  Uint16 itemNamesCount = map.getItemNamesCount();

  terrainSurfaces = new SDL_Surface*[terrainNamesCount];
  itemSurfaces = new SDL_Surface*[itemNamesCount];

  int i;
  for (i = 0; i < terrainNamesCount; i++) {
    char file[256];
    sprintf(
      file, "../%s/%s_%d.png",
      imagesFolder.c_str(), map.getTerrainName(i).c_str(), imagesSize
    );
    terrainSurfaces[i] = loadImage(file);
  }
  for (i = 0; i < itemNamesCount; i++) {
    char file[256];
    sprintf(
      file, "../%s/%s_%d.png",
      imagesFolder.c_str(), map.getItemName(i).c_str(), imagesSize
    );
    itemSurfaces[i] = loadImage(file);
  }
}

void ScreenMap::unset() {
  delete[] terrainSurfaces;
  delete[] itemSurfaces;
}

SDL_Surface *ScreenMap::loadImage(string file) {
  SDL_Surface* loadedImage = NULL;
  SDL_Surface* optimizedImage = NULL;

  loadedImage = IMG_Load(file.c_str());
  if (loadedImage != NULL) {

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
