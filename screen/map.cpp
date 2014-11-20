#include "map.hpp"

void ScreenMap::init(Map *pMap, bool pHasGrid, bool pHasBuildings) {
  map = pMap;
  hasGrid = pHasGrid;
  hasBuildings = pHasBuildings;
  imageSize = 64;
  imagesFolder = "images";
  updateSize();

  resetFieldSelection();
  resetMove();

  Uint16 terrainNamesCount = map->getTerrainNamesCount();
  Uint16 itemNamesCount = map->getItemNamesCount();

  terrainSurfaces = new SDL_Surface*[terrainNamesCount];
  itemSurfaces = new SDL_Surface*[itemNamesCount];

  Uint16 buildingNamesCount = 0;
  if (hasBuildings == true) {
    buildingNamesCount = map->getBuildingNamesCount();
    buildingSurfaces = new SDL_Surface*[buildingNamesCount];
  }

  int i;
  string file;
  for (i = 0; i < terrainNamesCount; i++) {
    file = imagesFolder + "/terrain/" + map->getTerrainName(i) + "_"
      + to_string(imageSize) + ".png";
    terrainSurfaces[i] = loadImage(file);
  }
  for (i = 0; i < itemNamesCount; i++) {
    file = imagesFolder + "/items/" + map->getItemName(i) + "_"
      + to_string(imageSize) + ".png";
    itemSurfaces[i] = loadImage(file);
  }
  if (buildingNamesCount > 0) {
    for (i = 0; i < buildingNamesCount; i++) {
      file = imagesFolder + "/buildings/" + map->getBuildingName(i) + "_"
        + to_string(imageSize) + ".png";
      buildingSurfaces[i] = loadImage(file);
    }
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

bool ScreenMap::selectField(Uint16 screenX, Uint16 screenY) {
  fieldSelection.column = -1 * (rect.x - screenX) / imageSize;
  fieldSelection.row = -1 * (rect.y - screenY) / imageSize;
  if (fieldSelection.column >= columns || fieldSelection.row >= rows) {
    resetFieldSelection();
    return false;
  }
  return true;
}

int ScreenMap::getFieldSelectionColumn() {
  return fieldSelection.column;
}

int ScreenMap::getFieldSelectionRow() {
  return fieldSelection.row;
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
  Uint16 terrain, item, resource, building;
  y = rect.y;
  for (row = 0; row < rows; row++) {
    x = rect.x;
    for (col = 0; col < columns; col++) {
      if (x + imageSize > 0 && y + imageSize > 0 &&
          x < surface->w && y < surface->h) {
        terrain = map->getField(row, col, "terrain");
        apply(x, y, terrainSurfaces[terrain]);
        item = map->getField(row, col, "item");
        if (item > 0)
          apply(x, y, itemSurfaces[item]);
        if (hasBuildings == true) {
          building = map->getField(row, col, "building");
          if (building > 0)
            apply(x, y, buildingSurfaces[building]);
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
  if (hasBuildings == true) {
    delete[] buildingSurfaces;
  }
}
