#include "global.h"
#include "map.h"
#include "tlist.h"

#define FALSE 0
#define TRUE 1

#define FPS 15

SDL_Surface *screen;
SDL_Surface *message;

int screen_width = 800;
int screen_height = 600;
int screen_bpp = 32;

char window_title_str[256] = "Project Z - Editor";
char window_footer_str[256];

char font_file[128] = "resources/beyourself.ttf";
TTF_Font *font = NULL;
SDL_Color font_color = { 255, 255, 255 };
int font_size = 24;

SDL_Event event;
int leftMouseButtonDown = FALSE;
int rightMouseButtonDown = FALSE;

extern int map_rows;
extern int map_cols;

enum {
  MODE_MAP,
  MODE_LIST
};
int mode = MODE_MAP;

int init() {
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
    return FALSE;
  }

  screen = SDL_SetVideoMode(
    screen_width, screen_height, screen_bpp, SDL_SWSURFACE | SDL_RESIZABLE
  );
  if (screen == NULL) {
    return FALSE;
  }

  if (TTF_Init() == -1) {
    return FALSE;
  }

  SDL_WM_SetCaption(window_title_str, NULL);

  map_init();
  list_init();

  return TRUE;
}

int load_files() {
  font = TTF_OpenFont(font_file, font_size);
  if (font == NULL) {
    return FALSE;
  }

  return TRUE;
}

int set_footer_message() {
  SDL_FreeSurface(message);
  sprintf(window_footer_str, "%d/%d", map_cols, map_rows);
  message = TTF_RenderText_Solid(font, window_footer_str, font_color);
  if (message == NULL) {
    return FALSE;
  }
  return TRUE;
}

void clean_up() {
  list_clean_up();
  map_clean_up();

  SDL_FreeSurface(message);

  TTF_CloseFont(font);
  TTF_Quit();

  SDL_Quit();
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
  SDL_Rect offset;
  offset.x = x;
  offset.y = y;

  SDL_BlitSurface(source, NULL, destination, &offset);
}

void handle_map_event() {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_RIGHT)
      rightMouseButtonDown = TRUE;
    else if (event.button.button == SDL_BUTTON_LEFT) {
      leftMouseButtonDown = TRUE;
      map_select_tile(event.button.x, event.button.y, list_get_selected_item());
    }
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_RIGHT) {
      rightMouseButtonDown = FALSE;
      map_move_reset();
    } else if (event.button.button == SDL_BUTTON_LEFT) {
      leftMouseButtonDown = FALSE;
    }
  }
  if (event.type == SDL_MOUSEMOTION) {
    if (rightMouseButtonDown == TRUE) {
      map_move(event.button.x, event.button.y);
    } else if (leftMouseButtonDown == TRUE) {
      map_select_tile(event.button.x, event.button.y, list_get_selected_item());
    }
  }
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
      case SDLK_g: map_toggle_grid(); break;
      case SDLK_PLUS: map_resize(1); set_footer_message(); break;
      case SDLK_MINUS: map_resize(-1); set_footer_message(); break;
      case SDLK_l: map_load(); set_footer_message(); break;
      case SDLK_s: map_save(); break;
      default: ;
    }
  }
}

void handle_list_event() {
  if (event.type == SDL_MOUSEBUTTONDOWN &&
      event.button.button == SDL_BUTTON_LEFT) {
    leftMouseButtonDown = TRUE;
    if (list_is_scrollbar_active() == FALSE) {
      list_select_entry_item(event.button.y);
    }
  }

  if (event.type == SDL_MOUSEBUTTONUP) {
    if (event.button.button == SDL_BUTTON_WHEELUP) {
      list_change_offset(TRUE, 10.f);
    } else if (event.button.button == SDL_BUTTON_WHEELDOWN) {
      list_change_offset(FALSE, 10.f);
    } else {
      leftMouseButtonDown = FALSE;
    }
  }

  if (event.type == SDL_MOUSEMOTION) {
    if (list_set_scrollbar_active(event.motion.x, event.motion.y) == TRUE &&
        leftMouseButtonDown == TRUE) {
      list_move_scrollbar_slider(event.button.y);
    }
  }
}

void toggle_mode() {
  mode = (mode == MODE_MAP) ? MODE_LIST : MODE_MAP;
}

int main(int argc, char* args[]) {
  if (init() == FALSE) {
    return 1;
  }
  if (load_files() == FALSE) {
    return 1;
  }

  if (set_footer_message() == FALSE)
    return 1;

  Uint32 frameStart = 0;
  int quit = FALSE;
  while (quit == FALSE) {
    frameStart = SDL_GetTicks();

    while (SDL_PollEvent(&event)) {
      if (mode == MODE_MAP) {
        handle_map_event();
      } else {
        handle_list_event();
      }
      if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_TAB: toggle_mode(); break;
          case SDLK_ESCAPE: quit = TRUE; map_save(); break;
          default: ;
        }
      }
      if(event.type == SDL_VIDEORESIZE) {
        screen_width = event.resize.w;
        screen_height = event.resize.h;
        screen = SDL_SetVideoMode(
          screen_width, screen_height, screen_bpp, SDL_SWSURFACE | SDL_RESIZABLE
        );
      }
      if (event.type == SDL_QUIT) {
        quit = TRUE;
        map_save();
      }
    }

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

    if (mode == MODE_MAP) {
      map_show();
      apply_surface(
        screen_width - message->w, screen_height - message->h, message, screen
      );
    } else {
      list_show();
      list_scrollbar_show();
    }
    if (SDL_Flip(screen) == -1) {
      return 1;
    }

    if ((SDL_GetTicks() - frameStart) < (1000 / FPS)) {
      SDL_Delay((1000 / FPS) - (SDL_GetTicks() - frameStart));
    }
  }

  clean_up();
  return 0;
}
