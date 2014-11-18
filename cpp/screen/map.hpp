#ifndef _INCLUDE_SCREEN_MAP_HPP
#define _INCLUDE_SCREEN_MAP_HPP

#include "../global.hpp"
#include "../surface.hpp"
#include "../map.hpp"

class ScreenMap: public Surface {
  Map map;
  SDL_Rect rect;
  Uint16 rows;
  Uint16 columns;
  Uint16 imageSize;
  string imagesFolder;
  SDL_Surface **terrainSurfaces;
  SDL_Surface **itemSurfaces;
public:
  void init(Map&);
  void showGrid();
  void unset();
  SDL_Surface *loadImage(string file);
};

#endif
