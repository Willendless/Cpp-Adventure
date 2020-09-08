#include <stdio.h>
#include "debug.h"

int main() {
    printf("Hello world!\n");
    check(1==1, "abc");
    return 0;
error:
    return -1;
}
