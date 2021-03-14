#include <stdlib.h>
#include <stdio.h>
#include "void_string.c"
#include "ascii_string.c"
#include "unicode_string.c"
#include "utf8_string.c"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "ru-RU.1251");

    stringMetadata *ascii = CreateASCIIStringMeta();
    stringMetadata *utf8 = CreateUTF8StringMeta();
    stringMetadata *unicode = CreateUNICODEStringMeta();
    char *a = calloc(5, 1);
    scanf("%s", a);
    a[4] = '\0';
    voidString *b = CreateFromCharArray(unicode, strlen(a) + 1, a);
//    b->stringMeta->ToHigher(b);
    printf("%s\n", a);
    printf("%d\n", 'A'- 'a');
    free(a);
    free(ascii);
    free(utf8);
    free(unicode);
    return 0;
}
