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

// json parser
#include "../jsmn/jsmn.h"

#define FALSE 0
#define TRUE 1

enum {
  MODE_EDITOR,
  MODE_EDITOR_MAP,
  MODE_EDITOR_LIST,
  MODE_GAME
};

#endif
