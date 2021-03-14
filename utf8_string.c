//
// Created by korna on 09.03.2021.
//
#include "utf8_string.h"
#include <assert.h>
#include <stdint.h>

typeMetadata *CreateUTF8Meta() {
  return CreateTypeMeta(sizeof(char) * 4, UTF8IsEqual, UTF8ToUTF8,
                        UTF8ToUNICODE, UTF8ToASCII, UTF8Lower, UTF8Higher,
                        SetUTF8Locale, ScanUTF8, PrintUTF8);
}

void SetUTF8Locale() { setlocale(LC_ALL, "ru-RU.UTF8"); }

void *ScanUTF8() {
  wchar_t *res = calloc(4, sizeof(char));
  *res = getwchar();
  return res;
}

void PrintUTF8(void *el) { printf("%c", *(char *)el); }

int UTF8IsValid(void *character) {
  assert(character != NULL);
  assert(((unsigned char *)character)[0] < 128 ||
         (((unsigned char *)character)[0] >= 128 &&
          ((unsigned char *)character)[0] <= 191));
  return 1;
}

int UTF8IsEqual(void *character1, void *character2) {
  int len1 = UTF8GetLen(character1);
  int len2 = UTF8GetLen(character2);
  if (len1 != len2)
    return 0;
  for (int i = 0; i < len1; ++i) {
    if (((char *)character1)[i] != ((char *)character2)[i])
      return 0;
  }
  return 1;
}

int UTF8GetLen(void *character) {
  assert(UTF8IsValid(character));
  int res = 1;
  if (*((unsigned char *)character) > 128)
    while ((*((unsigned char *)character + res) >= 128 &&
            *((unsigned char *)character + res) <= 191) &&
           res < 4)
      res++;
  return res;
}

void *UTF8ToUTF8(void *character) { return character; }

void *UTF8ToUNICODE(void *character) {
  assert(0);
  return NULL;
}

void *UTF8ToASCII(void *character) {
  assert(0);
  return NULL;
}

void *UTF8Lower(void *character) {
  int len = UTF8GetLen(character);
  unsigned char *res = calloc(len, sizeof(char));
  if (len == 1 && *(unsigned char *)character >= 65 &&
      *(unsigned char *)character <= 90)
    res[0] = *(unsigned char *)character + 32;
  else if (len == 2 && *(uint16_t *)character >= 53392 &&
           *(uint16_t *)character <= 53407)
    *(uint16_t *)res = *(uint16_t *)character + 32;
  else if (len == 2 && *(uint16_t *)character >= 53408 &&
           *(uint16_t *)character <= 53423)
    *(uint16_t *)res = *(uint16_t *)character + 224;
  else if (len == 2 && *(uint16_t *)character == 53377)
    *(uint16_t *)res = 53649;
  return res;
}

void *UTF8Higher(void *character) {
  int len = UTF8GetLen(character);
  unsigned char *res = calloc(len, sizeof(char));
  if (len == 1 && *(unsigned char *)character >= 97 &&
      *(unsigned char *)character <= 122)
    res[0] = *(unsigned char *)character - 32;
  else if (len == 2 && *(uint16_t *)character >= 53424 &&
           *(uint16_t *)character <= 53439)
    *(uint16_t *)res = *(uint16_t *)character - 32;
  else if (len == 2 && *(uint16_t *)character >= 53632 &&
           *(uint16_t *)character <= 53647)
    *(uint16_t *)res = *(uint16_t *)character - 224;
  else if (len == 2 && *(uint16_t *)character == 53649)
    *(uint16_t *)res = 53377;
  return res;
}
