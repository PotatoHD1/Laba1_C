//
// Created by korna on 09.03.2021.
//

#include "ascii_string.h"
#include <assert.h>
#include <locale.h>
#include <stdio.h>

typeMetadata *CreateASCIIMeta(char **errorlog) {
  return CreateTypeMeta(sizeof(char), ASCIIIsEqual, ASCIIToUTF8, ASCIIToUNICODE,
                        ASCIIToASCII, ASCIILower, ASCIIHigher, SetASCIILocale,
                        PrintASCII, PreprocessASCIIStr, errorlog);
}

void SetASCIILocale(char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "SetASCIILocale");
  setlocale(LC_ALL, "ru-RU.1251");
  RemoveFromLog(errorlog);
}

void PrintASCII(void *el, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "PrintASCII");
  printf("%c", *(char *)el);
  RemoveFromLog(errorlog);
}

bool ASCIIIsValid(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "ASCIIIsValid");
  assert(character != NULL);
  RemoveFromLog(errorlog);
  return true;
}

bool ASCIIIsEqual(void *character1, void *character2, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "ASCIIIsEqual");
  assert(ASCIIIsValid(character1, errorlog) &&
         ASCIIIsValid(character2, errorlog));
  RemoveFromLog(errorlog);
  return *(char *)character1 == *(char *)character2;
}

void *ASCIIToUTF8(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "ASCIIToUTF8");
  assert(ASCIIIsValid(character, errorlog));
  char *res;
  res = calloc(1, 1);
  *(res) = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *ASCIIToUNICODE(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "ASCIIToUNICODE");
  assert(ASCIIIsValid(character, errorlog));
  char *res;
  res = calloc(1, 1);
  *(res) = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *ASCIIToASCII(void *character, char **errorlog) { return character; }

void *ASCIILower(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "ASCIILower");
  char *res = (char *)calloc(1, 1);
  if (*(char *)character >= 'A' && *(char *)character <= 'Z')
    *res = 'a' - 'A' + *(char *)character;
  else
    *res = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *ASCIIHigher(void *character, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "ASCIIHigher");
  char *res = (char *)calloc(1, 1);
  if (*(char *)character >= 'a' && *(char *)character <= 'z')
    *res = 'A' - 'a' + *(char *)character;
  else
    *res = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *PreprocessASCIIStr(void *str, char **errorlog) { return str; }
