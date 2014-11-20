#ifndef _INCLUDE_MAP_HPP
#define _INCLUDE_MAP_HPP

#include "global.hpp"
#include "json.hpp"
#include "lists.hpp"

struct stMapField {
  Uint16 terrain;
  Uint16 item;
  Uint16 resources;
  Uint16 building;
};

class Map {
  string file;
  Uint16 columns;
  Uint16 rows;
  stMapField **fields;
  Lists *lists;
public:
  Map();
  void increaseSize(Uint8);
  void decreaseSize(Uint8);
  void load();
  void save();
  void set(bool);
  void setLists(Lists *);
  void unset();
  void setField(Uint16, Uint16, Uint16, string);
  Uint16 getField(Uint16, Uint16, string);
  bool fieldHasItem(Uint16, Uint16);
  Uint16 getColumns();
  Uint16 getRows();
  Uint16 getTerrainNamesCount();
  string getTerrainName(int);
  Uint16 getItemNamesCount();
  string getItemName(int);
  Uint16 getBuildingNamesCount();
  string getBuildingName(int);
};

#endif
