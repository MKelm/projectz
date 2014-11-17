#include "map.hpp"

Map::Map() {
  file = "../data/map.json";
  rows = 12;
  columns = 12;
}

void Map::load() {
  JsonLoader loader(file);
  int i = loader.set();
  if (i > 0) {
    unsigned int type = loader.getTokenType(0);
    string token = loader.getToken(0);
    if (loader.getTokenType(0) == JSMN_OBJECT) {
      cout << "token with type " << token << " - " << type << endl;
    }
  }
  loader.unset();
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
