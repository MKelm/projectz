#include "global.h"
#include "map.h"
#include "tiles.h"

#define FALSE 0
#define TRUE 1

extern SDL_Surface *screen;
extern int screen_width;
extern int screen_height;
extern struct st_tile tiles[TILES_MAX];

int map_rows = 1;
int map_cols = 1;
int **map;
int map_set = FALSE;
int map_show_grid = TRUE;

struct st_map_tile_selection {
  int row;
  int col;
} map_tile_selection;

SDL_Rect map_rect;
SDL_Rect map_move_rect;

void map_set_map() {
  if (map_set == TRUE) {
    free(map);
  }

  map_rect.x = 0;
  map_rect.y = 0;
  map_rect.w = map_cols * TILES_SIZE;
  map_rect.h = map_rows * TILES_SIZE;
  map_tile_selection_reset();

  int i;
  map = (int **) malloc(map_rows * sizeof(int *));
  for (i = 0; i < map_rows; i++)
    map[i] = (int *) malloc(map_cols * sizeof(int));

  int row, col;
  for (row = 0; row < map_rows; row++) {
    for (col = 0; col < map_cols; col++) {
      map[row][col] = 0;
    }
  }

  map_set = TRUE;
}

void map_init() {
  tiles_init();

  map_set_map();
  map_move_reset();

  map_load();
}

void map_load() {
  FILE *fp;
  if ((fp = fopen("data/map_size.dat", "r")) != NULL) {
    int i = 0;
    char chunk[1024];
    char *chunk_part;
    while (fgets(chunk, 1024, fp) != NULL) {
      chunk_part = strtok(chunk, " ");
      while (chunk_part != NULL) {
        if (i == 0)
          map_cols = atoi(chunk_part);
        else
          map_rows = atoi(chunk_part);
        chunk_part = strtok(NULL, " ");
        i++;
      }
    }
    fclose(fp);
    map_set_map();
  }
  if ((fp = fopen("data/map_terrain.dat", "r")) != NULL) {
    int row = 0, col = 0;
    char chunk[1024];
    char *chunk_part;
    while (fgets(chunk, 1024, fp) != NULL) {
      col = 0;
      chunk_part = strtok(chunk, " ");
      while (chunk_part != NULL) {
        if (col < map_cols && row < map_rows) {
          map[row][col] = atoi(chunk_part);
        }
        chunk_part = strtok(NULL, " ");
        col++;
      }
      row++;
    }
    fclose(fp);
  }
}

void map_save() {
  FILE *fp;
  char c[3];
  if ((fp = fopen("data/map_size.dat", "w")) != NULL) {
    sprintf(c, "%s%d ", map_cols < 10 ? "0" : "", map_cols);
    fputs(c, fp);
    sprintf(c, "%s%d", map_rows < 10 ? "0" : "", map_rows);
    fputs(c, fp);
    fclose(fp);
  }
  if ((fp = fopen("data/map_terrain.dat", "w")) != NULL) {
    int row, col;
    for (row = 0; row < map_rows; row++) {
      for (col = 0; col < map_cols; col++) {
        sprintf(
          c, "%s%d%s",
          map[row][col] < 10 ? "0" : "",
          map[row][col] < 0 ? 0 : map[row][col],
          col + 1 < map_cols ? " " : ""
        );
        fputs(c, fp);
      }
      if (row + 1 < map_rows) {
        sprintf(c, "\n");
        fputs(c, fp);
      }
    }
    fclose(fp);
  }
}

void map_resize(int direction) {
  if (direction == 1) {
    map_rows++;
    map_cols++;
  } else if (map_rows > 1 && map_cols > 1) {
    map_rows--;
    map_cols--;
  }
  map_set_map();
}

void map_toggle_grid() {
  map_show_grid = (map_show_grid == TRUE) ? FALSE : TRUE;
}

void map_show() {
  SDL_Rect offset;
  int row, col, x, y;
  y = map_rect.y;
  for (row = 0; row < map_rows; row++) {
    x = map_rect.x;
    for (col = 0; col < map_cols; col++) {
      offset.x = x;
      offset.y = y;
      if (offset.x + TILES_SIZE > 0 && offset.y + TILES_SIZE > 0 &&
          offset.x < screen_width && offset.y < screen_height &&
          map[row][col] > -1) {
        SDL_BlitSurface(tiles[map[row][col]].tile, NULL, screen, &offset);
      }
      x += TILES_SIZE;
    }
    y += TILES_SIZE;
  }

  if (map_show_grid == TRUE) {
    int row, col, x, y;
    y = map_rect.y;
    for (row = 0; row < map_rows; row++) {
      x = map_rect.x;
      if (y > 0 && y < screen_height) {
        lineRGBA(
          screen, x, y, x + map_rect.w, y,
          255, 255, 255, 255
        );
      }
      for (col = 0; col < map_cols; col++) {
        if (x > 0 && x < screen_width) {
          lineRGBA(
            screen, x, y, x, y + map_rect.h - row * TILES_SIZE,
            255, 255, 255, 255
          );
        }
        x += TILES_SIZE;
      }
      if (x > 0 && x < screen_width) {
        lineRGBA(
          screen, x, y, x, y + map_rect.h - row * TILES_SIZE,
          255, 255, 255, 255
        );
      }
      y += TILES_SIZE;
    }
    x = map_rect.x;
    if (y > 0 && y < screen_height) {
      lineRGBA(
        screen, x, y, x + map_rect.w, y,
        255, 255, 255, 255
      );
    }
  }

  if (map_tile_selection.col > -1 && map_tile_selection.row > -1) {
    rectangleRGBA(
      screen,
      map_rect.x + map_tile_selection.col * TILES_SIZE,
      map_rect.y + map_tile_selection.row * TILES_SIZE,
      map_rect.x + map_tile_selection.col * TILES_SIZE + TILES_SIZE,
      map_rect.y + map_tile_selection.row * TILES_SIZE + TILES_SIZE,
      255, 0, 0, 255
    );
  }
}

void map_set_tile(int col, int row, int tile_id) {
  if (tile_id > -1)
    map[row][col] = tile_id;
}

void map_select_tile(int screen_x, int screen_y, int tile_id) {
  map_tile_selection.col = -1 * (map_rect.x - screen_x) / TILES_SIZE;
  map_tile_selection.row = -1 * (map_rect.y - screen_y) / TILES_SIZE;
  if (map_tile_selection.col >= map_cols || map_tile_selection.row >= map_rows)
    map_tile_selection_reset();
  else
    map_set_tile(map_tile_selection.col, map_tile_selection.row, tile_id);
}

void map_tile_selection_reset() {
  map_tile_selection.row = -1;
  map_tile_selection.col = -1;
}

void map_move(int x, int y) {
  if (map_move_rect.x > -1 && map_move_rect.y > -1) {
    map_rect.x -= map_move_rect.x - x;
    map_rect.y -= map_move_rect.y - y;
  }
  map_move_rect.x = x;
  map_move_rect.y = y;
}

void map_move_reset() {
  map_move_rect.x = -1;
  map_move_rect.y = -1;
}

void map_clean_up() {
  tiles_clean_up();
  free(map);
}
