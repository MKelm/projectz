#ifndef _INCLUDE_LIST_HPP
#define _INCLUDE_LIST_HPP

#include "global.hpp"
#include "json.hpp"

struct stListEntry {
  string name;
  string title;
  string description;
};

class Lists {
  string file;
public:
  Uint16 terrainLength;
  Uint16 itemsLength;
  Uint16 buildingsLength;
  stListEntry *terrain;
  stListEntry *items;
  stListEntry *buildings;
  Lists();
  void load();
  void unset();
};

#endif
