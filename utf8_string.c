//
// Created by korna on 09.03.2021.
//
#include "utf8_string.h"
#include <assert.h>
#include <stdint.h>

typeMetadata *CreateUTF8Meta(char **errorlog) {
  return CreateTypeMeta(sizeof(char) * 4, UTF8IsEqual, UTF8ToUTF8,
                        UTF8ToUNICODE, UTF8ToASCII, UTF8Lower, UTF8Higher,
                        SetUTF8Locale, ScanUTF8, PrintUTF8, PreprocessUFT8Str,
                        errorlog);
}

void SetUTF8Locale(char **errorlog) {
  char funcName[] = "SetUTF8Locale";
  AddToLog(errorlog, funcName);
  setlocale(LC_ALL, "ru-RU.UTF8");
  RemoveFromLog(errorlog);
}

void *ScanUTF8(char **errorlog) {
  char funcName[] = "ScanUTF8";
  AddToLog(errorlog, funcName);
  wchar_t *res = calloc(4, sizeof(char));
  *res = getwchar();
  RemoveFromLog(errorlog);
  return res;
}

void PrintUTF8(void *el, char **errorlog) {
  char funcName[] = "PrintUTF8";
  AddToLog(errorlog, funcName);
  printf("%s", (char *)el);
  RemoveFromLog(errorlog);
}

bool UTF8IsValid(void *character, char **errorlog) {
  char funcName[] = "UTF8IsValid";
  AddToLog(errorlog, funcName);
  assert(character != NULL);
  assert(((unsigned char *)character)[0] < 128 ||
         (((unsigned char *)character)[0] >= 128 &&
          ((unsigned char *)character)[0] <= 191));
  RemoveFromLog(errorlog);
  return true;
}

bool UTF8IsEqual(void *character1, void *character2, char **errorlog) {
  char funcName[] = "UTF8IsEqual";
  AddToLog(errorlog, funcName);
  int len1 = UTF8GetLen(character1, errorlog);
  int len2 = UTF8GetLen(character2, errorlog);
  if (len1 != len2) {
    RemoveFromLog(errorlog);
    return false;
  }
  for (int i = 0; i < len1; ++i) {
    if (((char *)character1)[i] != ((char *)character2)[i]) {
      RemoveFromLog(errorlog);
      return false;
    }
  }
  RemoveFromLog(errorlog);
  return true;
}

int UTF8GetLen(void *character, char **errorlog) {
  char funcName[] = "UTF8GetLen";
  AddToLog(errorlog, funcName);
  assert(UTF8IsValid(character, errorlog));
  int res = 1;
  if (*((unsigned char *)character) > 128)
    while ((*((unsigned char *)character + res) >= 128 &&
            *((unsigned char *)character + res) <= 191) &&
           res < 4)
      res++;
  RemoveFromLog(errorlog);
  return res;
}

void *UTF8ToUTF8(void *character, char **errorlog) { return character; }

void *UTF8ToUNICODE(void *character, char **errorlog) {
  char funcName[] = "UTF8ToUNICODE";
  AddToLog(errorlog, funcName);
  assert(0);
  RemoveFromLog(errorlog);
  return NULL;
}

void *UTF8ToASCII(void *character, char **errorlog) {
  char funcName[] = "UTF8ToASCII";
  AddToLog(errorlog, funcName);
  assert(0);
  RemoveFromLog(errorlog);
  return NULL;
}

void *UTF8Lower(void *character, char **errorlog) {
  char funcName[] = "UTF8Lower";
  AddToLog(errorlog, funcName);
  int len = UTF8GetLen(character, errorlog);
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
  RemoveFromLog(errorlog);
  return res;
}

void *UTF8Higher(void *character, char **errorlog) {
  char funcName[] = "UTF8Higher";
  AddToLog(errorlog, funcName);
  int len = UTF8GetLen(character, errorlog);
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
  RemoveFromLog(errorlog);
  return res;
}

void *PreprocessUTF8Str(void *str, char **errorlog) {
  char funcName[] = "PreprocessUTF8Str";
  AddToLog(errorlog, funcName);
  int len = strlen((char *)str);
  char *res = calloc(1, sizeof(char) * 4 * len + 1);
  int local_len = 0;
  int symbols = 0;
  //  int local_len = UTF8GetLen(str, errorlog);

  while (local_len <= len) {
    int tmp = UTF8GetLen(str + local_len, errorlog);
    memcpy(res + symbols * sizeof(char) * 4, str + local_len, tmp);
    symbols++;
    local_len += tmp;
  }
  RemoveFromLog(errorlog);
  return res;
}