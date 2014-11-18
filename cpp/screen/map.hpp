#ifndef _INCLUDE_SCREEN_MAP_HPP
#define _INCLUDE_SCREEN_MAP_HPP

#include "../global.hpp"
#include "../surface.hpp"
#include "../map.hpp"

class ScreenMap: public Surface {
  Map map;
  bool hasGrid;
  SDL_Rect rect;
  SDL_Rect moveRect;
  Uint16 rows;
  Uint16 columns;
  Uint16 imageSize;
  string imagesFolder;
  SDL_Surface **terrainSurfaces;
  SDL_Surface **itemSurfaces;
  struct stFieldSelection {
    int column;
    int row;
  } fieldSelection;
public:
  void init(Map&);
  void toggleGrid();
  void resetMove();
  void moveSet(Uint16, Uint16);
  void resetFieldSelection();
  void selectField(Uint16, Uint16);
  void showFieldSelection();
  void showGrid();
  void unset();
  SDL_Surface *loadImage(string file);
};

#endif
