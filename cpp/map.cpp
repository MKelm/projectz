#include "map.hpp"

Map::Map() {
  file = "../data/map.json";
  rows = 12;
  columns = 12;
}

void Map::load() {
  JsonLoader loader(file);
  int r = loader.set();
  if (r > 0) {
    int i = 0, j, j_max, k, k_max, l, l_max;
    string token;
    string fieldsType;

    if (loader.getTokenType(i) == JSMN_OBJECT) {
      j_max = loader.getTokenSize(i);
      for (j = 0; j < j_max; j++) {
        i++;
        if (loader.getTokenType(i) == JSMN_STRING) {
          token = loader.getToken(i);
          if (token == "cols") {
            columns = atoi(loader.getToken(i+1).c_str());
          } else if (token == "rows") {
            rows = atoi(loader.getToken(i+1).c_str());
          } else if (token == "terrain" || token == "items" || token == "resources") {
            i++;
            if (loader.getTokenType(i) == JSMN_ARRAY) {
              fieldsType = token;
              k_max = loader.getTokenSize(i);
              for (k = 0; k < k_max; k++) {
                i++;
                if (loader.getTokenType(i) == JSMN_ARRAY) {
                  l_max = loader.getTokenSize(i);
                  for (l = 0; l < l_max; l++) {
                    i++;
                    if (fieldsType == "terrain")
                      terrain[k][l] = atoi(loader.getToken(i).c_str());
                    else if (fieldsType == "items")
                      items[k][l] = atoi(loader.getToken(i).c_str());
                    else if (fieldsType == "resources")
                      resources[k][l] = atoi(loader.getToken(i).c_str());
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
  loader.unset();
}

void Map::save() {
  string json = "{ \n\"cols\" : " + to_string(columns) +
    ", \n\"rows\" : " + to_string(rows) +", \n";

  int typeIdx = 0;
  string types[3] = { "terrain", "items", "resources" };

  for (typeIdx = 0; typeIdx < 3; typeIdx++) {
    json += "\"" + types[typeIdx] + "\" : [ \n";
    int row, col;
    for (row = 0; row < rows; row++) {
      json += " [ ";
      for (col = 0; col < columns; col++) {
        if (types[typeIdx] == "terrain")
          json += to_string(terrain[row][col]);
        else if (types[typeIdx] == "items")
          json += to_string(items[row][col]);
        else if (types[typeIdx] == "resources")
          json += to_string(resources[row][col]);

        json += (col + 1 < columns) ? ", " : "";
      }
      json += " ]";
      json += (row + 1 < rows) ? ", \n" : " \n";
    }
    json += " ]";
    json += (typeIdx + 1 < 3) ? ", \n" : " \n";
  }

  json += "}\n";
  cout << json << endl;
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

  int row, col;
  for (row = 0; row < rows; row++) {
    for (col = 0; col < columns; col++) {
      terrain[row][col] = -1;
      items[row][col] = -1;
      resources[row][col] = -1;
    }
  }
}

void Map::unset() {
  free(terrain);
  free(items);
  free(resources);
}
