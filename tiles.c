#include "global.h"
#include "tiles.h"

struct st_tile tiles[TILES_MAX];

SDL_Surface* tile_image;

char folder[128] = "resources";
char tile_names[TILES_MAX][128] = {
  "grass", "sand", "dirt", "water", "rock"
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
  for (i = 0; i < TILES_MAX; i++) {
    char file[256];
    sprintf(file, "%s/%s_%d.png", folder, tile_names[i], TILES_SIZE);
    tiles[i].tile = tiles_load_img(file);
  }
}

void tiles_clean_up() {
  int i;
  for (i = 0; i < TILES_MAX; i++) {
    SDL_FreeSurface(tiles[i].tile);
  }
}
