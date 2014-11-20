#ifndef _INCLUDE_SCREEN_MAP_HPP
#define _INCLUDE_SCREEN_MAP_HPP

#include "../global.hpp"
#include "../surface.hpp"
#include "../map.hpp"

struct stMapFieldSelection {
  int column;
  int row;
};

class ScreenMap: public Surface {
  Map *map;
  bool hasGrid;
  bool hasBuildings;
  SDL_Rect rect;
  SDL_Rect moveRect;
  Uint16 rows;
  Uint16 columns;
  Uint16 imageSize;
  string imagesFolder;
  SDL_Surface **terrainSurfaces;
  SDL_Surface **itemSurfaces;
  SDL_Surface **buildingSurfaces;
  stMapFieldSelection fieldSelection;
public:
  void init(Map *, bool, bool);
  void updateSize();
  string getSizeString();
  void toggleGrid();
  void resetMove();
  void moveSet(Uint16, Uint16);
  void resetFieldSelection();
  bool selectField(Uint16, Uint16);
  int getFieldSelectionColumn();
  int getFieldSelectionRow();
  void showFieldSelection();
  void show();
  void showGrid();
  void unset();
};

#endif
