#include "stdio.h"
#include <stdlib.h>


// will assure that it won't be inlined function, thus be called by pointers only
// gcc could potentially inline it as it's really small function.
// alternatively there's gcc command -fno-inline
__attribute__ ((noinline))
unsigned long factorial(unsigned long acc, unsigned long arg) {
    if (arg == 0) {
        return acc;
    }
    return factorial(acc * arg, arg - 1);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        puts("Please provide only one argument");
        return 1;
    }
    unsigned long val = strtoul(argv[1], NULL, 0);
    printf("%ld\n", factorial(1, val));
    return 0;
}