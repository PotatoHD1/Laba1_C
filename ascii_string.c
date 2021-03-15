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
                        ScanASCII, PrintASCII, PreprocessASCIIStr, errorlog);
}

void SetASCIILocale(char **errorlog) {
  char funcName[] = "SetASCIILocale";
  AddToLog(errorlog, funcName);
  setlocale(LC_ALL, "ru-RU.1251");
  RemoveFromLog(errorlog);
}

void *ScanASCII(char **errorlog) {
  char funcName[] = "ScanASCII";
  AddToLog(errorlog, funcName);
  char *res = calloc(1, sizeof(char));
  *res = getchar();
  RemoveFromLog(errorlog);
  return res;
}

void PrintASCII(void *el, char **errorlog) {
  char funcName[] = "PrintASCII";
  AddToLog(errorlog, funcName);
  printf("%c", *(char *)el);
  RemoveFromLog(errorlog);
}

bool ASCIIIsValid(void *character, char **errorlog) {
  char funcName[] = "ASCIIIsValid";
  AddToLog(errorlog, funcName);
  assert(character != NULL);
  RemoveFromLog(errorlog);
  return true;
}

bool ASCIIIsEqual(void *character1, void *character2, char **errorlog) {
  char funcName[] = "ASCIIIsEqual";
  AddToLog(errorlog, funcName);
  assert(ASCIIIsValid(character1, errorlog) &&
         ASCIIIsValid(character2, errorlog));
  RemoveFromLog(errorlog);
  return *(char *)character1 == *(char *)character2;
}

void *ASCIIToUTF8(void *character, char **errorlog) {
  char funcName[] = "ASCIIToUTF8";
  AddToLog(errorlog, funcName);
  assert(ASCIIIsValid(character, errorlog));
  char *res;
  res = calloc(1, 1);
  *(res) = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *ASCIIToUNICODE(void *character, char **errorlog) {
  char funcName[] = "ASCIIToUNICODE";
  AddToLog(errorlog, funcName);
  assert(ASCIIIsValid(character, errorlog));
  char *res;
  res = calloc(1, 1);
  *(res) = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *ASCIIToASCII(void *character, char **errorlog) { return character; }

void *ASCIILower(void *character, char **errorlog) {
  char funcName[] = "ASCIILower";
  AddToLog(errorlog, funcName);
  char *res = (char *)calloc(1, 1);
  if (*(char *)character >= 'A' && *(char *)character <= 'Z')
    *res = 'a' - 'A' + *(char *)character;
  else
    *res = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *ASCIIHigher(void *character, char **errorlog) {
  char funcName[] = "ASCIIHigher";
  AddToLog(errorlog, funcName);
  char *res = (char *)calloc(1, 1);
  if (*(char *)character >= 'a' && *(char *)character <= 'z')
    *res = 'A' - 'a' + *(char *)character;
  else
    *res = *(char *)character;
  RemoveFromLog(errorlog);
  return res;
}

void *PreprocessASCIIStr(void *str, char **errorlog) { return errorlog; }
