#include <stdio.h>
#include <stdlib.h>
#include "void_string.c"
#include "ascii_string.c"
#include "unicode_string.c"
#include "utf8_string.c"
int main() {

  typeMetadata *ascii = CreateASCIIMeta();
  typeMetadata *utf8 = CreateUTF8Meta();
  typeMetadata *unicode = CreateUNICODEMeta();
  //    a[4] = '\0';
  //    voidString *b = CreateFromCharArray(unicode, strlen(a) + 1, a);
  //    b->stringMeta->ToHigher(b);
  free(ascii);
  free(utf8);
  free(unicode);
  return 0;
}
