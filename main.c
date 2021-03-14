#include <stdio.h>
#include "void_string.c"
#include "ascii_string.c"
#include "unicode_string.c"
#include "utf8_string.c"

int main() {
    stringMetadata *ascii = CreateASCIIStringMeta();
    stringMetadata *utf8 = CreateUTF8StringMeta();
    stringMetadata *unicode = CreateUNICODEStringMeta();
    char a[] = "qwertyuiop";
    voidString *b = CreateFromCharArray(ascii, strlen(a) + 1, a);
    b->stringMeta->ToHigher(b);
    printf("%s\n", (char *) b->data);
    return 0;
}
