#include "global.hpp"
#include "main.hpp"

int main(int argc, char* args[]) {
  Main main(15, MODE_EDITOR);
  main.loop();
  main.quit();
}
