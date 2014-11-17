#ifndef _INCLUDE_SCREEN_MAP_HPP
#define _INCLUDE_SCREEN_MAP_HPP

#include "../global.hpp"
#include "../map.hpp"

class ScreenMap {
  Map map;
  Uint16 imagesSize;
  string imagesFolder;
  SDL_Surface **terrainSurfaces;
  SDL_Surface **itemSurfaces;
public:
  void init(Map&);
  void unset();
  SDL_Surface *loadImage(string file);
};

#endif
