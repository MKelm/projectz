#ifndef _INCLUDE_GLOBAL_HPP
#define _INCLUDE_GLOBAL_HPP

// cpp components
#include <string>
#include <iostream>
using namespace std;

// sdl components
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_gfxPrimitives.h"

#define FALSE 0
#define TRUE 1

enum {
  MODE_EDITOR,
  MODE_GAME
};

enum {
  SUB_MODE_EDITOR_MAP,
  SUB_MODE_EDITOR_MAP_INPUT,
  SUB_MODE_EDITOR_LIST,
  SUB_MODE_GAME_MENU,
  SUB_MODE_GAME_MAP,
  SUB_MODE_GAME_LIST
};

#endif
