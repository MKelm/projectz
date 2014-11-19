#include "map.hpp"

Map::Map() {
  file = "data/map.json";
  rows = 12;
  columns = 12;
}

void Map::increaseSize(Uint8 value) {
  rows += value;
  columns += value;
  #ifdef DEBUG
    cout << "map rows/cols " << rows << "/" << columns << endl;
  #endif
  unset();
  set();
}

void Map::decreaseSize(Uint8 value) {
  rows -= value;
  columns -= value;
  #ifdef DEBUG
    cout << "map rows/cols " << rows << "/" << columns << endl;
  #endif
  unset();
  set();
}

void Map::load() {
  Json json(file);
  int r = json.load();
  if (r > 0) {
    bool mapInitialized = false;
    int i = 0, j, j_max, k, k_max, l, l_max;
    string token;
    string fieldsType;

    if (json.getTokenType(i) == JSMN_OBJECT) {
      j_max = json.getTokenSize(i);
      for (j = 0; j < j_max; j++) {
        i++;
        if (json.getTokenType(i) == JSMN_STRING) {
          token = json.getToken(i);
          if (token == "cols") {
            columns = atoi(json.getToken(i+1).c_str());
          } else if (token == "rows") {
            rows = atoi(json.getToken(i+1).c_str());
          } else if (token == "terrain" || token == "items" || token == "resources") {
            if (mapInitialized == false) {
              set();
              mapInitialized = true;
            }
            i++;
            if (json.getTokenType(i) == JSMN_ARRAY) {
              fieldsType = token;
              k_max = json.getTokenSize(i);
              for (k = 0; k < k_max; k++) {
                i++;
                if (json.getTokenType(i) == JSMN_ARRAY) {
                  l_max = json.getTokenSize(i);
                  for (l = 0; l < l_max; l++) {
                    i++;
                    if (fieldsType == "terrain")
                      terrain[k][l] = atoi(json.getToken(i).c_str());
                    else if (fieldsType == "items")
                      items[k][l] = atoi(json.getToken(i).c_str());
                    else if (fieldsType == "resources")
                      resources[k][l] = atoi(json.getToken(i).c_str());
                  }
                }
              }
            }
            i--;
          }
        }
      }
    }
  }
  json.unload();
}

void Map::save() {
  string jsonStr = "{ \n\"cols\" : " + to_string(columns) +
    ", \n\"rows\" : " + to_string(rows) +", \n";

  int typeIdx = 0;
  string types[3] = { "terrain", "items", "resources" };

  for (typeIdx = 0; typeIdx < 3; typeIdx++) {
    jsonStr += "\"" + types[typeIdx] + "\" : [ \n";
    int row, col;
    for (row = 0; row < rows; row++) {
      jsonStr += " [ ";
      for (col = 0; col < columns; col++) {
        if (types[typeIdx] == "terrain")
          jsonStr += to_string(terrain[row][col]);
        else if (types[typeIdx] == "items")
          jsonStr += to_string(items[row][col]);
        else if (types[typeIdx] == "resources")
          jsonStr += to_string(resources[row][col]);

        jsonStr += (col + 1 < columns) ? ", " : "";
      }
      jsonStr += " ]";
      jsonStr += (row + 1 < rows) ? ", \n" : " \n";
    }
    jsonStr += " ]";
    jsonStr += (typeIdx + 1 < 3) ? ", \n" : " \n";
  }
  jsonStr += "}\n";

  Json json(file);
  json.set(jsonStr);
  json.save();
}

void Map::setNames(Lists *lists) {
  int i;
  terrainNamesCount = lists->terrainLength;
  terrainNames = new string[terrainNamesCount];
  for (i = 0; i < terrainNamesCount; i++) {
    terrainNames[i] = lists->terrain[i].name;
  }

  itemNamesCount = lists->itemsLength;
  itemNames = new string[itemNamesCount];
  for (i = 0; i < itemNamesCount; i++) {
    itemNames[i] = lists->items[i].name;
  }
}

void Map::set() {
  int i;
  terrain = (Uint16 **) malloc(rows * sizeof(Uint16 *));
  items = (Uint16 **) malloc(rows * sizeof(Uint16 *));
  resources = (Uint16 **) malloc(rows * sizeof(Uint16 *));
  for (i = 0; i < rows; i++) {
    terrain[i] = (Uint16 *) malloc(columns * sizeof(Uint16));
    items[i] = (Uint16 *) malloc(columns * sizeof(Uint16));
    resources[i] = (Uint16 *) malloc(columns * sizeof(Uint16));
  }
}

void Map::setField(Uint16 column, Uint16 row, Uint16 value, string type) {
  if (type == "terrain")
    terrain[row][column] = value;
  else if (type == "item")
    items[row][column] = value;
  else if (type == "resource")
    resources[row][column] = value;
}

Uint16 Map::getField(Uint16 row, Uint16 column, string type) {
  if (type == "terrain")
    return terrain[row][column];
  else if (type == "item")
    return items[row][column];
  else if (type == "resource")
    return resources[row][column];
}

bool Map::fieldHasItem(Uint16 column, Uint16 row) {
  return items[row][column] > 0;
}

Uint16 Map::getColumns() {
  return columns;
}

Uint16 Map::getRows() {
  return rows;
}

string Map::getTerrainName(int index) {
  return terrainNames[index];
}

Uint16 Map::getTerrainNamesCount() {
  return terrainNamesCount;
}

string Map::getItemName(int index) {
  return itemNames[index];
}

Uint16 Map::getItemNamesCount() {
  return itemNamesCount;
}

void Map::unset() {
  free(terrain);
  free(items);
  free(resources);
}
