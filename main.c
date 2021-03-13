#include <stdio.h>
#include "void_string.c"
#include "ascii_string.c"
#include "unicode_string.c"
#include "utf8_string.c"

int main() {
    stringMetadata *ascii = CreateASCIIStringMeta();
    char a[] = "qwertyuiop";
    voidString *b = CreateFromCharArray(ascii, strlen(a) + 1, a);
//    printf("%s\n");
    return 0;
}
