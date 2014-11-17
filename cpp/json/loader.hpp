#ifndef _INCLUDE_JSON_LOADER_HPP
#define _INCLUDE_JSON_LOADER_HPP

#include "../global.hpp"
#include <cstring>

class JsonLoader {
  string file;
  Uint8 mode;
  Uint16 chunkLength;
  string json;
  jsmntok_t *tokens;
public:
  JsonLoader(string);
  int set();
  string getToken(unsigned int);
  unsigned int getTokenType(unsigned int);
  string getJson();
  jsmntok_t *getTokens();
  void unset();
};

#endif
