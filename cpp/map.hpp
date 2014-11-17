#ifndef _INCLUDE_MAP_HPP
#define _INCLUDE_MAP_HPP

#include "global.hpp"
#include "json/loader.hpp"

class Map {
  string file;
  Uint16 columns;
  Uint16 rows;
  Uint16 **terrain;
  Uint16 **items;
  Uint16 **resources;
public:
  Map();
  void load();
  void save();
  void set();
  void unset();
};

#endif
