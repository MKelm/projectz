#ifndef _INCLUDE_JSON_HPP
#define _INCLUDE_JSON_HPP

#include "global.hpp"
#include "jsmn/jsmn.h"
#include <cstring>

class Json {
  string file;
  Uint16 chunkLength;
  string json;
  jsmntok_t *tokens;
public:
  Json(string);
  int load();
  string getToken(unsigned int);
  unsigned int getTokenType(unsigned int);
  unsigned int getTokenSize(unsigned int);
  void set(string);
  int save();
  void unload();
};

#endif
