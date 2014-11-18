#include "map.hpp"

void ScreenMap::init(Map *pMap, bool pHasGrid) {
  map = pMap;
  hasGrid = pHasGrid;
  imageSize = 64;
  imagesFolder = "images";
  updateSize();

  resetFieldSelection();
  resetMove();

  Uint16 terrainNamesCount = map->getTerrainNamesCount();
  Uint16 itemNamesCount = map->getItemNamesCount();

  terrainSurfaces = new SDL_Surface*[terrainNamesCount];
  itemSurfaces = new SDL_Surface*[itemNamesCount];

  int i;
  for (i = 0; i < terrainNamesCount; i++) {
    char file[256];
    sprintf(
      file, "../%s/%s_%d.png",
      imagesFolder.c_str(), map->getTerrainName(i).c_str(), imageSize
    );
    terrainSurfaces[i] = loadImage(file);
  }
  for (i = 0; i < itemNamesCount; i++) {
    char file[256];
    sprintf(
      file, "../%s/%s_%d.png",
      imagesFolder.c_str(), map->getItemName(i).c_str(), imageSize
    );
    itemSurfaces[i] = loadImage(file);
  }
}

void ScreenMap::updateSize() {
  rows = map->getRows();
  columns = map->getColumns();
  rect.y = 0;
  rect.x = 0;
  rect.w = rows * imageSize;
  rect.h = columns * imageSize;
}

string ScreenMap::getSizeString() {
  #ifdef DEBUG
    cout << "screen map rows/cols " << map->getRows() << "/" << map->getColumns() << endl;
  #endif
  return to_string(map->getColumns()) + "/" + to_string(map->getRows());
}

void ScreenMap::toggleGrid() {
  hasGrid = (hasGrid == true) ? false : true;
}

void ScreenMap::resetMove() {
  moveRect.x = -1;
  moveRect.y = -1;
}

void ScreenMap::moveSet(Uint16 x, Uint16 y) {
  if (moveRect.x > -1 && moveRect.y > -1) {
    rect.x -= moveRect.x - x;
    rect.y -= moveRect.y - y;
  }
  moveRect.x = x;
  moveRect.y = y;
}

void ScreenMap::resetFieldSelection() {
  fieldSelection.row = -1;
  fieldSelection.column = -1;
}

void ScreenMap::selectField(Uint16 screenX, Uint16 screenY) {
  fieldSelection.column = -1 * (rect.x - screenX) / imageSize;
  fieldSelection.row = -1 * (rect.y - screenY) / imageSize;
  if (fieldSelection.column >= columns || fieldSelection.row >= rows) {
    resetFieldSelection();
  }
}

void ScreenMap::showFieldSelection() {
  if (fieldSelection.column > -1 && fieldSelection.row > -1) {
    rectangleRGBA(
      surface,
      rect.x + fieldSelection.column * imageSize,
      rect.y + fieldSelection.row * imageSize,
      rect.x + fieldSelection.column * imageSize + imageSize,
      rect.y + fieldSelection.row * imageSize + imageSize,
      255, 0, 0, 255
    );
  }
}

void ScreenMap::show() {
  int row, col, x, y;
  Uint16 terrain, item, resource;
  y = rect.y;
  for (row = 0; row < rows; row++) {
    x = rect.x;
    for (col = 0; col < columns; col++) {
      if (x + imageSize > 0 && y + imageSize > 0 &&
          x < surface->w && y < surface->h) {
        terrain = map->getField(row, col, "terrain");
        apply(x, y, terrainSurfaces[terrain]);
        item = map->getField(row, col, "item");
        if (item > 0) {
          apply(x, y, itemSurfaces[item]);
        }
      }
      x += imageSize;
    }
    y += imageSize;
  }
}

void ScreenMap::showGrid() {
  if (hasGrid == true) {
    int row, col, x, y;
    y = rect.y;
    for (row = 0; row < rows; row++) {
      x = rect.x;
      if (y > 0 && y < surface->h) {
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
      if (x > 0 && x < surface->w) {
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
