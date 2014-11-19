#include "global.hpp"
#include "main.hpp"

int main(int argc, char* args[]) {
  Main main(15, MODE_EDITOR, SUB_MODE_EDITOR_MAP);
  main.loop();
  main.quit();
}
