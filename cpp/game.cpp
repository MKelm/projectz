#include "global.hpp"
#include "main.hpp"

int main(int argc, char* args[]) {
  Main main(15, MODE_GAME, SUB_MODE_GAME_MENU);
  main.loop();
  main.quit();
}
