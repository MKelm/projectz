#include "global.h"
#include "tiles.h"

struct st_tile tiles_terrain[TILES_TERRAIN_MAX];
struct st_tile tiles_items[TILES_ITEMS_MAX];

char folder[128] = "images";
char tiles_terrain_names[TILES_TERRAIN_MAX][128] = {
  "grass", "sand", "dirt", "water", "rock"
};
char tiles_items_names[TILES_ITEMS_MAX][128] = {
  "empty", "trees", "rocks", "fishes", "gold", "coal", "ironore"
};

SDL_Surface *tiles_load_img(char *file_name) {
  SDL_Surface* loaded_image = NULL;
  SDL_Surface* optimized_image = NULL;

  loaded_image = IMG_Load(file_name);
  if (loaded_image != NULL) {

    optimized_image = SDL_DisplayFormat(loaded_image);
    SDL_FreeSurface(loaded_image);
    if (optimized_image != NULL) {
      SDL_SetColorKey(
        optimized_image, SDL_SRCCOLORKEY, SDL_MapRGB(optimized_image->format, 0, 0, 0)
      );
    }
  }

  return optimized_image;
}

void tiles_init() {
  int i;
  for (i = 0; i < TILES_TERRAIN_MAX; i++) {
    char file[256];
    sprintf(file, "%s/%s_%d.png", folder, tiles_terrain_names[i], TILES_SIZE);
    tiles_terrain[i].tile = tiles_load_img(file);
  }
  for (i = 0; i < TILES_ITEMS_MAX; i++) {
    char file[256];
    sprintf(file, "%s/%s_%d.png", folder, tiles_items_names[i], TILES_SIZE);
    tiles_items[i].tile = tiles_load_img(file);
  }
}

void tiles_clean_up() {
  int i;
  for (i = 0; i < TILES_TERRAIN_MAX; i++) {
    SDL_FreeSurface(tiles_terrain[i].tile);
  }
  for (i = 0; i < TILES_ITEMS_MAX; i++) {
    SDL_FreeSurface(tiles_items[i].tile);
  }
}
