
#include "shell.h"

int main() {

  for (;;) {
    get_command();
    run_command();
  }

  return 0;
}

