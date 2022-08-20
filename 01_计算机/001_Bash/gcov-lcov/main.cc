
#include <iostream>

int test(int x, int y) {
    if (x < y) {
        return x;
    } else if (x == y) {
        return y;
    } else {
        return y;
    }
    return 0;
}

int main(int argc, char *argv[]) {

    test(1, 1);
    test(1, 2);

    return 0;
}

