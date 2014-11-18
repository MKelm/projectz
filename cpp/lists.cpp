#include "lists.hpp"

Lists::Lists() {
  file = "../data/lists.json";
}

void Lists::load() {
  Json json(file);
  int r = json.load();
  if (r > 0) {
    Uint16 terrainIdx, itemsIdx;
    terrainIdx = itemsIdx = 0;
    int i = 0, j, j_max, k, k_max, l, l_max;
    string token;
    string itemType;

    if (json.getTokenType(i) == JSMN_OBJECT) {
      j_max = json.getTokenSize(i);
      for (j = 0; j < j_max; j++) {
        i++;
        if (json.getTokenType(i) == JSMN_STRING) {
          token = json.getToken(i);
          if (token == "length") {
            i++;
            if (json.getTokenType(i) == JSMN_OBJECT) {
              k_max = json.getTokenSize(i);
              for (k = 0; k < k_max; k++) {
                i++;
                token = json.getToken(i);
                if (token == "terrain") {
                  terrainLength = stoi(json.getToken(i+1));
                  terrain = new stListEntry[terrainLength];
                } else if (token == "items") {
                  itemsLength = stoi(json.getToken(i+1));
                  items = new stListEntry[itemsLength];
                }
              }
            }
            i--;
          } else if (token == "terrain" || token == "items") {
            i++;
            if (json.getTokenType(i) == JSMN_ARRAY) {
              itemType = token;
              k_max = json.getTokenSize(i);
              for (k = 0; k < k_max; k++) {
                i++;
                if (json.getTokenType(i) == JSMN_ARRAY) {
                  l_max = json.getTokenSize(i);
                  for (l = 0; l < l_max; l++) {
                    i++;
                    token = json.getToken(i);
                    if (l == 0) {
                      if (itemType == "terrain") {
                        terrain[terrainIdx].name = token;
                      } else if (itemType == "items") {
                        items[itemsIdx].name = token;
                      }
                    } else if (l == 1) {
                      if (itemType == "terrain") {
                        terrain[terrainIdx].title = token;
                      } else if (itemType == "items") {
                        items[itemsIdx].title = token;
                      }
                    } else if (l == 2) {
                      if (itemType == "terrain") {
                        terrain[terrainIdx].description = token;
                      } else if (itemType == "items") {
                        items[itemsIdx].description = token;
                      }
                    }
                  }
                  if (itemType == "terrain") {
                    terrainIdx++;
                  } else if (itemType == "items") {
                    itemsIdx++;
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

void Lists::unset() {
  delete[] terrain;
  delete[] items;
}
