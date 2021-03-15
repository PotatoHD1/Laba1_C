//
// Created by korna on 08.03.2021.
//
#include "void_string.h"
#include "stdlib.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

voidString *CreateString(typeMetadata *typeMeta, int len, char **errorlog) {
  char funcName[] = "CreateString";
  AddToLog(errorlog, funcName);
  assert(len > 0);
  assert(validTypeMeta(typeMeta, errorlog));
  voidString *res = (voidString *)calloc(1, sizeof(voidString));
  res->data = calloc(len, typeMeta->size + 1);
  res->len = len + 1;
  res->typeMeta = typeMeta;
  RemoveFromLog(errorlog);
  return res;
}
void AddToLog(char **errorlog, char text[]) {
  int len = strlen(*errorlog);
  //  if (len == 0) {
  //    *errorlog = realloc(*errorlog, 5);
  //    strcpy(*errorlog, "main");
  //    len = 4;
  //  }
  *errorlog = realloc(*errorlog, len + strlen(text) + 3 + 1);
  strcpy(*errorlog + len, " | ");
  strcpy(*errorlog + len + 3, text);
  (*errorlog)[len + strlen(text) + 3] = '\0';
}
void RemoveFromLog(char **errorlog) {
  int count = 0;
  int len = strlen(*errorlog);
  while (count <= len && *(*errorlog + count) != '|')
    count++;
  (*errorlog)[len - (count + 2)] = '\0';
}

bool IsLogError(char **errorlog, char text[]) {
  int count = 0;
  int len = strlen(*errorlog);
  while (count <= len && *(*errorlog + count) != '|')
    count++;
  return strcmp((*errorlog + len - count), text) != 0;
}
voidString *CreateFromCharArray(typeMetadata *typeMeta, int len, char *arr,
                                char **errorlog) {
  char funcName[] = "CreateFromCharArray";
  AddToLog(errorlog, funcName);
  assert(len > 0);
  assert(validTypeMeta(typeMeta, errorlog));
  char *data = typeMeta->PreprocessStr(arr, errorlog);
  voidString *res = (voidString *)calloc(1, sizeof(voidString));
  if (arr == data) {
    res->data = calloc(len, typeMeta->size + 1);
    memcpy(res->data, arr, len * typeMeta->size);
  } else
    res->data = data;
  res->len = len + 1;
  res->typeMeta = typeMeta;
  RemoveFromLog(errorlog);
  return res;
}

typeMetadata *CreateTypeMeta(
    int size, bool (*IsEqual)(void *, void *, char **),
    void *(*ToUTF8)(void *, char **), void *(*ToUNICODE)(void *, char **),
    void *(*ToASCII)(void *, char **), void *(*Lower)(void *, char **),
    void *(*Higher)(void *, char **), void (*SetLocale)(char **),
    void *(*Scan)(char **), void (*Print)(void *, char **),
    void *(*PreprocessStr)(void *, char **), char **errorlog) {
  char funcName[] = "CreateTypeMeta";
  AddToLog(errorlog, funcName);
  typeMetadata *res = (typeMetadata *)calloc(1, sizeof(typeMetadata));
  res->size = size;
  res->IsEqual = IsEqual;
  res->ToUTF8 = ToUTF8;
  res->ToUNICODE = ToUNICODE;
  res->ToASCII = ToASCII;
  res->Lower = Lower;
  res->Higher = Higher;
  res->SetLocale = SetLocale;
  res->Print = Print;
  res->Scan = Scan;
  res->PreprocessStr = PreprocessStr;
  RemoveFromLog(errorlog);
  return res;
}

bool equalTypeMeta(voidString *voidString1, voidString *voidString2,
                   char **errorlog) {
  char funcName[] = "equalTypeMeta";
  AddToLog(errorlog, funcName);
  assert(validStr(voidString1, errorlog) && validStr(voidString2, errorlog));
  RemoveFromLog(errorlog);
  return voidString1->typeMeta->size == voidString2->typeMeta->size &&
         voidString1->typeMeta->SetLocale == voidString2->typeMeta->SetLocale &&
         voidString1->typeMeta->IsEqual == voidString2->typeMeta->IsEqual &&
         voidString1->typeMeta->ToUTF8 == voidString2->typeMeta->ToUTF8 &&
         voidString1->typeMeta->ToUNICODE == voidString2->typeMeta->ToUNICODE &&
         voidString1->typeMeta->ToASCII == voidString2->typeMeta->ToASCII &&
         voidString1->typeMeta->Lower == voidString2->typeMeta->Lower &&
         voidString1->typeMeta->Higher == voidString2->typeMeta->Higher &&
         voidString1->typeMeta->Scan == voidString2->typeMeta->Scan &&
         voidString1->typeMeta->Print == voidString2->typeMeta->Print;
}

bool validTypeMeta(typeMetadata *typeMetadata, char **errorlog) {
  char funcName[] = "validTypeMeta";
  AddToLog(errorlog, funcName);
  assert(typeMetadata != NULL);
  assert(typeMetadata->size > 0);
  assert(typeMetadata->SetLocale != NULL);
  assert(typeMetadata->IsEqual != NULL);
  assert(typeMetadata->ToUTF8 != NULL);
  assert(typeMetadata->ToUNICODE != NULL);
  assert(typeMetadata->ToASCII != NULL);
  assert(typeMetadata->Lower != NULL);
  assert(typeMetadata->Higher != NULL);
  assert(typeMetadata->Scan != NULL);
  assert(typeMetadata->Print != NULL);
  RemoveFromLog(errorlog);
  return true;
}

bool validStr(voidString *voidStr, char **errorlog) {
  char funcName[] = "validStr";
  AddToLog(errorlog, funcName);
  assert(voidStr != NULL);
  assert(voidStr->data != NULL);
  assert(voidStr->len > 0);
  assert(validTypeMeta(voidStr->typeMeta, errorlog));
  RemoveFromLog(errorlog);
  return true;
}

voidString *Concat(voidString *voidStr1, voidString *voidStr2,
                   char **errorlog) {
  char funcName[] = "Concat";
  AddToLog(errorlog, funcName);
  assert(equalTypeMeta(voidStr1, voidStr2, errorlog));
  voidString *res = CreateString(voidStr1->typeMeta,
                                 voidStr1->len + voidStr2->len - 2, errorlog);
  memcpy(res->data, voidStr1->data,
         (voidStr1->len - 1) * voidStr1->typeMeta->size);
  memcpy(GetI(res, voidStr1->len - 1, errorlog), voidStr2->data,
         (voidStr2->len - 1) * voidStr2->typeMeta->size);
  RemoveFromLog(errorlog);
  return res;
}

voidString *Recode(void *(*func)(void *, char **), voidString *voidStr,
                   typeMetadata *newtypeMeta, char **errorlog) {
  char funcName[] = "Recode";
  AddToLog(errorlog, funcName);
  assert(func != NULL && validStr(voidStr, errorlog));
  voidString *res = CreateString(newtypeMeta, voidStr->len - 1, errorlog);
  for (int i = 0; i < voidStr->len; ++i) {
    void *tmp = func(GetI(voidStr, i, errorlog), errorlog);
    assert(tmp != NULL);
    memcpy(GetI(res, i, errorlog), tmp, voidStr->typeMeta->size);
    free(tmp);
  }
  RemoveFromLog(errorlog);
  return res;
}

bool Contains(voidString *voidStr1, voidString *voidStr2, int start, int n,
              char **errorlog) {
  char funcName[] = "Contains";
  AddToLog(errorlog, funcName);
  assert(equalTypeMeta(voidStr1, voidStr2, errorlog));
  assert(start >= 0 && n >= 0);
  if (voidStr2->len > (voidStr1->len - start) || voidStr2->len < n) {
    RemoveFromLog(errorlog);
    return false;
  }

  for (int i = start; i < start + n; ++i)
    if (!voidStr1->typeMeta->IsEqual(GetI(voidStr1, i, errorlog),
                                     GetI(voidStr1, i - start, errorlog),
                                     errorlog)) {
      RemoveFromLog(errorlog);
      return false;
    }
  RemoveFromLog(errorlog);
  return true;
}

void Map(void *(*func)(void *, char **), voidString *voidStr, char **errorlog) {
  char funcName[] = "Map";
  AddToLog(errorlog, funcName);
  assert(func != NULL && validStr(voidStr, errorlog));
  for (int i = 0; i < voidStr->len; ++i) {
    void *tmp = func(GetI(voidStr, i, errorlog), errorlog);
    assert(tmp != NULL);
    memcpy(GetI(voidStr, i, errorlog), tmp, voidStr->typeMeta->size);
    free(tmp);
  }
  RemoveFromLog(errorlog);
}

void ToLower(voidString *str, char **errorlog) {
  char funcName[] = "ToLower";
  AddToLog(errorlog, funcName);
  Map(str->typeMeta->Lower, str, errorlog);
  RemoveFromLog(errorlog);
}

void ToHigher(voidString *str, char **errorlog) {
  char funcName[] = "ToHigher";
  AddToLog(errorlog, funcName);
  Map(str->typeMeta->Higher, str, errorlog);
  RemoveFromLog(errorlog);
}

void ScanStr(voidString *str, char **errorlog) {
  char funcName[] = "ScanStr";
  AddToLog(errorlog, funcName);
  for (int i = 0; i < str->len; ++i) {
    void *temp = str->typeMeta->Scan(errorlog);
    memcpy(GetI(str, i, errorlog), temp, str->typeMeta->size);
    free(temp);
  }
  RemoveFromLog(errorlog);
}

voidString *CreateFromScanf(typeMetadata *typeMeta, int len, char **errorlog) {
  char funcName[] = "CreateFromScanf";
  AddToLog(errorlog, funcName);
  assert(len > 0);
  assert(validTypeMeta(typeMeta, errorlog));
  voidString *res = (voidString *)calloc(1, sizeof(voidString));
  res->data = calloc(len, typeMeta->size);
  for (int i = 0; i < len; ++i) {
    void *temp = typeMeta->Scan(errorlog);
    memcpy((char *)res->data + i * typeMeta->size, temp, typeMeta->size);
    free(temp);
  }
  res->len = len;
  res->typeMeta = typeMeta;
  RemoveFromLog(errorlog);
  return res;
}

void PrintStr(voidString *str, char **errorlog) {
  char funcName[] = "PrintStr";
  AddToLog(errorlog, funcName);
  str->typeMeta->SetLocale(errorlog);
  for (int i = 0; i < str->len; ++i) {
    str->typeMeta->Print(GetI(str, i, errorlog), errorlog);
  }
  printf("\n");
  RemoveFromLog(errorlog);
}

void *StrStr(voidString *voidStr1, voidString *voidStr2, int lower,
             char **errorlog) {
  char funcName[] = "StrStr";
  AddToLog(errorlog, funcName);
  assert(equalTypeMeta(voidStr1, voidStr2, errorlog));
  assert(lower == 0 || lower == 1);
  if (lower) {
    ToLower(voidStr1, errorlog);
    ToLower(voidStr2, errorlog);
  }
  int start = 0;
  while (start <= voidStr1->len) {
    if (Contains(voidStr1, voidStr2, start, voidStr1->len, errorlog)) {
      RemoveFromLog(errorlog);
      return GetI(voidStr1, start, errorlog);
    }
    start++;
  }
  RemoveFromLog(errorlog);
  return NULL;
}

voidString *Substring(int a, int b, voidString *voidStr, char **errorlog) {
  char funcName[] = "Substring";
  AddToLog(errorlog, funcName);
  assert(validStr(voidStr, errorlog));
  assert(a >= 0);
  assert(b > a);
  voidString *res = CreateString(voidStr->typeMeta, b - a + 1, errorlog);

  res->data = memcpy(res->data, GetI(voidStr, a, errorlog),
                     (b - a + 1) * voidStr->typeMeta->size);
  RemoveFromLog(errorlog);
  return res;
}

void Delete(voidString *voidStr, char **errorlog) {
  char funcName[] = "Delete";
  AddToLog(errorlog, funcName);
  assert(voidStr != NULL);
  if (voidStr->data != NULL) {
    voidStr->data = realloc(voidStr->data, 1);
    free(voidStr->data);
  }
  free(voidStr);
  RemoveFromLog(errorlog);
}

void *GetI(voidString *voidStr, int i, char **errorlog) {
  char funcName[] = "GetI";
  AddToLog(errorlog, funcName);
  assert(validStr(voidStr, errorlog));
  assert(i >= 0);
  assert(i < voidStr->len);
  RemoveFromLog(errorlog);
  return (char *)(voidStr->data) + i * (voidStr->typeMeta->size);
}
