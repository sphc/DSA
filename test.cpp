#include <iostream>

int main() {
    int *a{new int[100]};
    a[101] = 2;
    return 0;
}