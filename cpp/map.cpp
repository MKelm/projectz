#include "map.hpp"

Map::Map() {
  file = "../data/map.json";
  rows = 12;
  columns = 12;
}

void Map::increaseSize(Uint8 value) {
  rows += value;
  columns += value;
  #ifdef DEBUG
    cout << "map rows/cols " << rows << "/" << columns << endl;
  #endif
}

void Map::decreaseSize(Uint8 value) {
  rows -= value;
  columns -= value;
  #ifdef DEBUG
    cout << "map rows/cols " << rows << "/" << columns << endl;
  #endif
}

void Map::load() {
  Json json(file);
  int r = json.load();
  if (r > 0) {
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

void Map::set() {
  terrainNamesCount = 5;
  terrainNames = new string[terrainNamesCount];
  terrainNames[0] = "grass";
  terrainNames[1] = "sand";
  terrainNames[2] = "dirt";
  terrainNames[3] = "water";
  terrainNames[4] = "rock";

  itemNamesCount = 7;
  itemNames = new string[itemNamesCount];
  itemNames[0] = "empty";
  itemNames[1] = "trees";
  itemNames[2] = "rocks";
  itemNames[3] = "fishes";
  itemNames[4] = "gold";
  itemNames[5] = "coal";
  itemNames[6] = "ironore";

  int i;
  terrain = (Uint16 **) malloc(rows * sizeof(Uint16 *));
  items = (Uint16 **) malloc(rows * sizeof(Uint16 *));
  resources = (Uint16 **) malloc(rows * sizeof(Uint16 *));
  for (i = 0; i < rows; i++) {
    terrain[i] = (Uint16 *) malloc(columns * sizeof(Uint16));
    items[i] = (Uint16 *) malloc(columns * sizeof(Uint16));
    resources[i] = (Uint16 *) malloc(columns * sizeof(Uint16));
  }

  int row, col;
  for (row = 0; row < rows; row++) {
    for (col = 0; col < columns; col++) {
      terrain[row][col] = -1;
      items[row][col] = -1;
      resources[row][col] = -1;
    }
  }
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
  return terrainNames[index];
}

Uint16 Map::getItemNamesCount() {
  return terrainNamesCount;
}

void Map::unset() {
  free(terrain);
  free(items);
  free(resources);
}
