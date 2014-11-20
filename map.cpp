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
  set(true);
}

void Map::decreaseSize(Uint8 value) {
  rows -= value;
  columns -= value;
  #ifdef DEBUG
    cout << "map rows/cols " << rows << "/" << columns << endl;
  #endif
  unset();
  set(true);
}

void Map::load() {
  Json json(file);
  int r = json.load();
  if (r > 0) {
    bool mapHasValues = false;
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
            if (mapHasValues == false) {
              set(true);
              mapHasValues = true;
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
                      fields[k][l].terrain = atoi(json.getToken(i).c_str());
                    else if (fieldsType == "items")
                      fields[k][l].item = atoi(json.getToken(i).c_str());
                    else if (fieldsType == "resources")
                      fields[k][l].resources = atoi(json.getToken(i).c_str());
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
    int row, column;
    for (row = 0; row < rows; row++) {
      jsonStr += " [ ";
      for (column = 0; column < columns; column++) {
        if (types[typeIdx] == "terrain")
          jsonStr += to_string(fields[row][column].terrain);
        else if (types[typeIdx] == "items")
          jsonStr += to_string(fields[row][column].item);
        else if (types[typeIdx] == "resources")
          jsonStr += to_string(fields[row][column].resources);

        jsonStr += (column + 1 < columns) ? ", " : "";
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

void Map::set(bool setNewValues) {
  int i;
  fields = new stMapField*[rows];
  for (i = 0; i < rows; ++i) {
    fields[i] = new stMapField[columns];
  }

  if (setNewValues == true) {
    int row, column;
    for (row = 0; row < rows; row++) {
      for (column = 0; column < columns; column++) {
        fields[row][column].terrain = 0;
        fields[row][column].item = 0;
        fields[row][column].resources = 0;
        fields[row][column].building = 0;
      }
    }
  }
}

void Map::setField(Uint16 column, Uint16 row, Uint16 value, string type) {
  if (type == "terrain" && value > 0)
    fields[row][column].terrain = value;
  else if (type == "item")
    fields[row][column].item = value;
  else if (type == "resource")
    fields[row][column].resources = value;
  else if (type == "building")
    fields[row][column].building = value;
}

Uint16 Map::getField(Uint16 row, Uint16 column, string type) {
  if (type == "terrain")
    return fields[row][column].terrain;
  else if (type == "item")
    return fields[row][column].item;
  else if (type == "resource")
    return fields[row][column].resources;
  else if (type == "building")
    return fields[row][column].building;
}

bool Map::fieldHasItem(Uint16 column, Uint16 row) {
  return fields[row][column].item > 0;
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
  for (int i = 0; i < rows; ++i) {
    delete[] fields[i];
  }
  delete[] fields;
}
