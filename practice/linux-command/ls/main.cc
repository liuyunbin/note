
#include "ls.h"

int main(int argc, char *argv[]) {

  if (argc == 1) {
    ls(".");
  } else {
    for (int i = 1; i < argc; ++i) {
      ls(argv[i]);
    }
  }

  return 0;
}

