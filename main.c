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
  ascii->SetLocale();
  char *a = calloc(5, 1);
  scanf("%s", a);
  //  char a[] = "П\0\0О\0\0Ш\0\0Ё\0\0Л\0\0 \0\0\0Н\0\0А\0\0Х\0\0У\0\0Й\0\0";
  //    a[4] = '\0';
  voidString *b = CreateFromCharArray(ascii, strlen(a), a);
  voidString *c = Recode(b->typeMeta->ToUNICODE, b, unicode);
  voidString *d = Recode(b->typeMeta->ToUTF8, b, utf8);
  //    b->stringMeta->ToHigher(b);
  ToLower(b);
  ToLower(c);
  ToLower(d);
  PrintStr(b);
  PrintStr(c);
  PrintStr(d);
  free(a);
  Delete(c);
  Delete(b);
  Delete(d);
  free(ascii);
  free(utf8);
  free(unicode);
  return 0;
}
