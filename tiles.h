#define TILES_TERRAIN_MAX 5
#define TILES_ITEMS_MAX 7
#define TILES_SIZE 64

struct st_tile {
  SDL_Surface *tile;
};

void tiles_init();
void tiles_clean_up();
