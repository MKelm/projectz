#include "map.hpp"

void ScreenMap::init(Map& p_map) {
  map = p_map;
  rows = map.getRows();
  columns = map.getRows();
  imageSize = 64;
  rect.y = 0;
  rect.x = 0;
  rect.w = rows * imageSize;
  rect.h = columns * imageSize;

  Uint16 terrainNamesCount = map.getTerrainNamesCount();
  Uint16 itemNamesCount = map.getItemNamesCount();

  terrainSurfaces = new SDL_Surface*[terrainNamesCount];
  itemSurfaces = new SDL_Surface*[itemNamesCount];

  int i;
  for (i = 0; i < terrainNamesCount; i++) {
    char file[256];
    sprintf(
      file, "../%s/%s_%d.png",
      imagesFolder.c_str(), map.getTerrainName(i).c_str(), imageSize
    );
    terrainSurfaces[i] = loadImage(file);
  }
  for (i = 0; i < itemNamesCount; i++) {
    char file[256];
    sprintf(
      file, "../%s/%s_%d.png",
      imagesFolder.c_str(), map.getItemName(i).c_str(), imageSize
    );
    itemSurfaces[i] = loadImage(file);
  }
}

void ScreenMap::showGrid() {
  bool mapShowGrid = true;

  if (mapShowGrid == true) {
    int row, col, x, y;
    y = rect.y;
    for (row = 0; row < rows; row++) {
      x = rect.x;
      if (y > 0 && y < surface->w) {
        lineRGBA(
          surface, x, y, x + rect.w, y,
          255, 255, 255, 255
        );
      }
      for (col = 0; col < columns; col++) {
        if (x > 0 && x < surface->w) {
          lineRGBA(
            surface, x, y, x, y + rect.h - row * imageSize,
            255, 255, 255, 255
          );
        }
        x += imageSize;
      }
      if (x > 0 && x < surface->h) {
        lineRGBA(
          surface, x, y, x, y + rect.h - row * imageSize,
          255, 255, 255, 255
        );
      }
      y += imageSize;
    }
    x = rect.x;
    if (y > 0 && y < surface->h) {
      lineRGBA(
        surface, x, y, x + rect.w, y,
        255, 255, 255, 255
      );
    }
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
