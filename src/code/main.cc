
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <vector>

int main() {

  int sum  = 0;

  for (int  i = 0; i < 1000000; ++i)
     sum += i;

  std::cout << sum << std::endl;

  return 0;
}

