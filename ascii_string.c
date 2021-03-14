//
// Created by korna on 09.03.2021.
//

#include "ascii_string.h"
#include <assert.h>
#include <locale.h>

typeMetadata *CreateASCIIMeta() {
  return CreateTypeMeta(sizeof(char), ASCIIIsEqual, ASCIIToUTF8, ASCIIToUNICODE,
                        ASCIIToASCII, ASCIILower, ASCIIHigher, SetASCIILocale,
                        ScanASCII, PrintASCII);
}

void SetASCIILocale() { setlocale(LC_ALL, "ru-RU.1251"); }

void *ScanASCII() {
  char *res = calloc(1, sizeof(char));
  *res = getchar();
  return res;
}

void PrintASCII(void *el) { printf("%c", *(char *)el); }

int ASCIIIsValid(void *character) {
  assert(character != NULL);
  return 1;
}

int ASCIIIsEqual(void *character1, void *character2) {
  assert(ASCIIIsValid(character1) && ASCIIIsValid(character2));
  return *(char *)character1 == *(char *)character2;
}

void *ASCIIToUTF8(void *character) {
  assert(ASCIIIsValid(character));
  char *res;
  res = calloc(1, 1);
  *(res) = *(char *)character;
  return res;
}

void *ASCIIToUNICODE(void *character) {
  assert(ASCIIIsValid(character));
  char *res;
  res = calloc(1, 1);
  *(res) = *(char *)character;
  return res;
}

void *ASCIIToASCII(void *character) { return character; }

void *ASCIILower(void *character) {
  char *res = (char *)calloc(1, 1);
  if (*(char *)character >= 'A' && *(char *)character <= 'Z')
    *res = 'a' - 'A' + *(char *)character;
  else
    *res = *(char *)character;
  return res;
}

void *ASCIIHigher(void *character) {
  char *res = (char *)calloc(1, 1);
  if (*(char *)character >= 'a' && *(char *)character <= 'z')
    *res = 'A' - 'a' + *(char *)character;
  else
    *res = *(char *)character;
  return res;
}
