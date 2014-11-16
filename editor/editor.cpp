#include "global.hpp"
#include "screen.hpp"

#define FPS 15

int main(int argc, char* args[]) {
  Screen screen(640, 480, 32, MODE_EDITOR);
  screen.quit();
}
