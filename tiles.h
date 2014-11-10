#define TILES_MAX 5
#define TILES_SIZE 64

struct st_tile {
  SDL_Surface *tile;
};

void tiles_init();
void tiles_clean_up();
