#include <stdio.h>
#include "void_string.c"

int main() {
    char *a = "ass";
    for(int i = 0; i < 10; i++)
        printf("%d\n", a[i]);
    return 0;
}
