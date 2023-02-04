#include "common.h"

int asm_test() {
    int i = 2;
    int* j = &i;
    int& k = i;
    return 3;
}