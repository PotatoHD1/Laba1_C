#define _CRT_SECURE_NO_WARNINGS
#include "void_string.c"
#include "ascii_string.c"
#include "unicode_string.c"
#include "utf8_string.c"
#include "tests.c"
#include <stdio.h>
#include <stdlib.h>
int main() {
  RunAllTests();
//  char **errorlog = NULL;
//  typeMetadata *ascii = CreateASCIIMeta(errorlog);
//  typeMetadata *utf8 = CreateUTF8Meta(errorlog);
//  typeMetadata *unicode = CreateUNICODEMeta(errorlog);
//  ascii->SetLocale(errorlog);
//  char *a = calloc(5, 1);
//  scanf("%s", a);
//  //  char a[] = "П\0\0О\0\0Ш\0\0Ё\0\0Л\0\0 \0\0\0Н\0\0А\0\0Х\0\0У\0\0Й\0\0";
//  //    a[4] = '\0';
//  voidString *b = CreateFromCharArray(ascii, strlen(a), a, errorlog);
//  voidString *c = Recode(b->typeMeta->ToUNICODE, b, unicode, errorlog);
//  voidString *d = Recode(b->typeMeta->ToUTF8, b, utf8, errorlog);
//  //    b->stringMeta->ToHigher(b);
//  ToLower(b, errorlog);
//  ToLower(c, errorlog);
//  ToLower(d, errorlog);
//
//  PrintStr(b, errorlog);
//  PrintStr(c, errorlog);
//  PrintStr(d, errorlog);
//
//  free(a);
//  Delete(c, errorlog);
//  Delete(b, errorlog);
//  Delete(d, errorlog);
//  free(*errorlog);
//  free(errorlog);
//  free(ascii);
//  free(utf8);
//  free(unicode);
  return 0;
}
