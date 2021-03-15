//
// Created by korna on 09.03.2021.
//

#include "unicode_string.h"
#include <assert.h>

typeMetadata *CreateUNICODEMeta(char **errorlog) {
  return CreateTypeMeta(sizeof(char), UNICODEIsEqual, UNICODEToUTF8,
                        UNICODEToUNICODE, UNICODEToASCII, UNICODELower,
                        UNICODEHigher, SetUNICODELocale, PrintUNICODE,
                        PreprocessUNICODEStr, errorlog);
}

void SetUNICODELocale(char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "SetUNICODELocale");
  setlocale(LC_ALL, "ru-RU.1251");
  RemoveFromLog(errorlog);
}

void PrintUNICODE(void *el, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "PrintUNICODE");
  printf("%c", *(char *)el);
  RemoveFromLog(errorlog);
}

bool UNICODEIsValid(void *character1, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "UNICODEIsValid");
  assert(character1 != NULL);
  RemoveFromLog(errorlog);
  return true;
}

bool UNICODEIsEqual(void *character1, void *character2, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "UNICODEIsEqual");
  assert(UNICODEIsValid(character1, errorlog) &&
         UNICODEIsValid(character2, errorlog));
  RemoveFromLog(errorlog);
  return *(unsigned char *)character1 == *(unsigned char *)character2;
}

void *UNICODEToUTF8(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "UNICODEToUTF8");
  assert(UNICODEIsValid(character, errorlog));
  unsigned char *res;
  if (*(unsigned char *)character < 128) {
    res = calloc(1, 1);
    *(res) = *(unsigned char *)character;
  } else {
    res = calloc(1, 2);
    *(res) = 0xC0 | (*(unsigned char *)character >> 6);
    *(res + 1) = 0x80 | (*(unsigned char *)character & 0x3f);
  }
  RemoveFromLog(errorlog);
  return res;
}

void *UNICODEToUNICODE(void *character, char **errorlog) { return character; }

void *UNICODEToASCII(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "UNICODEToASCII");
  assert(0);
  RemoveFromLog(errorlog);
  return NULL;
}

void *UNICODELower(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "UNICODELower");
  unsigned char *res = (unsigned char *)calloc(1, 1);
  if (*(char *)character >= 'A' && *(char *)character <= 'Z')
    *res = 'a' - 'A' + *(unsigned char *)character;
  else if (*(unsigned char *)character >= 128 &&
           *(unsigned char *)character <= 143)
    *res = 32 + *(unsigned char *)character;
  else if (*(unsigned char *)character >= 144 &&
           *(unsigned char *)character <= 159)
    *res = 80 + *(unsigned char *)character;
  else if (*(unsigned char *)character == 240)
    *res = 241;
  else
    *res = *(unsigned char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *UNICODEHigher(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "UNICODEHigher");
  unsigned char *res = (unsigned char *)calloc(1, 1);
  if (*(char *)character >= 'a' && *(char *)character <= 'z')
    *res = 'A' - 'a' + *(unsigned char *)character;
  else if (*(unsigned char *)character >= 160 &&
           *(unsigned char *)character <= 175)
    *res = *(unsigned char *)character - 32;
  else if (*(unsigned char *)character >= 224 &&
           *(unsigned char *)character <= 239)
    *res = *(unsigned char *)character - 80;
  else if (*(unsigned char *)character == 241)
    *res = 240;
  else
    *res = *(unsigned char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *PreprocessUNICODEStr(void *str, char **errorlog) { return str; }