//
// Created by korna on 08.03.2021.
//
#include "void_string.h"
#include "stdlib.h"
#include <assert.h>
#include <string.h>

voidString *CreateString(typeMetadata *typeMeta, int len) {
  assert(len > 0);
  assert(validTypeMeta(typeMeta));
  voidString *res = (voidString *)calloc(1, sizeof(voidString));
  res->data = calloc(len, typeMeta->size + 1);
  res->len = len + 1;
  res->typeMeta = typeMeta;
  return res;
}

voidString *CreateFromCharArray(typeMetadata *typeMeta, int len, char *arr) {
  assert(len > 0);
  assert(validTypeMeta(typeMeta));
  voidString *res = (voidString *)calloc(1, sizeof(voidString));
  res->data = calloc(len, typeMeta->size + 1);
  memcpy(res->data, arr, len * typeMeta->size);
  res->len = len + 1;
  res->typeMeta = typeMeta;
  return res;
}

typeMetadata *CreateTypeMeta(int size, int (*IsEqual)(void *, void *),
                             void *(*ToUTF8)(void *), void *(*ToUNICODE)(void *),
                             void *(*ToASCII)(void *), void *(*Lower)(void *),
                             void *(*Higher)(void *), void (*SetLocale)(),
                             void *(*Scan)(), void (*Print)(void *)) {
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
  return res;
}

// size_t size;
//
// void (*SetLocale)();
//
// int (*IsEqual)(void *, void *);
//
// void *(*ToUTF8)(void *);
//
// void *(*ToUNICODE)(void *);
//
// void *(*ToASCII)(void *);
//
// void *(*Lower)(void *);
//
// void *(*Higher)(void *);
//
// void *(*Scan)();
//
// void (*Print)(void *);
int equalTypeMeta(voidString *voidString1, voidString *voidString2) {
  assert(validStr(voidString1) && validStr(voidString2));
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

int validTypeMeta(typeMetadata *typeMetadata) {
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
  return 1;
}

int validStr(voidString *voidStr) {
  assert(voidStr != NULL);
  assert(voidStr->data != NULL);
  assert(voidStr->len > 0);
  assert(validTypeMeta(voidStr->typeMeta));
  return 1;
}

voidString *Concat(voidString *voidStr1, voidString *voidStr2) {
  assert(equalTypeMeta(voidStr1, voidStr2));
  voidString *res =
      CreateString(voidStr1->typeMeta, voidStr1->len + voidStr2->len - 2);
  memcpy(res->data, voidStr1->data, voidStr1->len * voidStr1->typeMeta->size);
  memcpy(GetI(res, voidStr1->len), voidStr2->data,
         voidStr2->len * voidStr2->typeMeta->size);
  return res;
}

voidString *Recode(void *(*func)(void *), voidString *voidStr,
                   typeMetadata *newtypeMeta) {
  assert(func != NULL && validStr(voidStr));
  voidString *res = CreateString(newtypeMeta, voidStr->len - 1);
  for (int i = 0; i < voidStr->len; ++i) {
    void *tmp = func(GetI(voidStr, i));
    assert(tmp != NULL);
    memcpy(GetI(res, i), tmp, voidStr->typeMeta->size);
    free(tmp);
  }
  return res;
}

int Contains(voidString *voidStr1, voidString *voidStr2, int start, int n) {
  assert(equalTypeMeta(voidStr1, voidStr2));
  assert(start >= 0 && n >= 0);
  if (voidStr2->len > (voidStr1->len - start) || voidStr2->len < n)
    return 0;

  for (int i = start; i < start + n; ++i)
    if (!voidStr1->typeMeta->IsEqual(GetI(voidStr1, i),
                                     GetI(voidStr1, i - start)))
      return 0;
  return 1;
}

void Map(void *(*func)(void *), voidString *voidStr) {
  assert(func != NULL && validStr(voidStr));
  for (int i = 0; i < voidStr->len; ++i) {
    void *tmp = func(GetI(voidStr, i));
    assert(tmp != NULL);
    memcpy(GetI(voidStr, i), tmp, voidStr->typeMeta->size);
    free(tmp);
  }
}

void ToLower(voidString *str) { Map(str->typeMeta->Lower, str); }

void ToHigher(voidString *str) { Map(str->typeMeta->Higher, str); }

void ScanStr(voidString *str) {
  for (int i = 0; i < str->len; ++i) {
    void *temp = str->typeMeta->Scan();
    memcpy(GetI(str, i), temp, str->typeMeta->size);
    free(temp);
  }
}

voidString *CreateFromScanf(typeMetadata *typeMeta, int len) {
  assert(len > 0);
  assert(validTypeMeta(typeMeta));
  voidString *res = (voidString *)calloc(1, sizeof(voidString));
  res->data = calloc(len, typeMeta->size);
  for (int i = 0; i < len; ++i) {
    void *temp = typeMeta->Scan();
    memcpy((char *)res->data + i * typeMeta->size, temp, typeMeta->size);
    free(temp);
  }
  res->len = len;
  res->typeMeta = typeMeta;
  return res;
}

void PrintStr(voidString *str) {
  str->typeMeta->SetLocale();
  for (int i = 0; i < str->len; ++i) {
    str->typeMeta->Print(GetI(str, i));
  }
  printf("\n");
}

void *StrStr(voidString *voidStr1, voidString *voidStr2, int lower) {
  assert(equalTypeMeta(voidStr1, voidStr2));
  assert(lower == 0 || lower == 1);
  if (lower) {
    ToLower(voidStr1);
    ToLower(voidStr2);
  }
  int start = 0;
  while (start <= voidStr1->len) {
    if (Contains(voidStr1, voidStr2, start, voidStr1->len))
      return GetI(voidStr1, start);
    start++;
  }

  return NULL;
}

voidString *Substring(int a, int b, voidString *voidStr) {
  assert(validStr(voidStr));
  voidString *res = CreateString(voidStr->typeMeta, b - a);
  res->data = memcpy(res->data, GetI(voidStr, a), b * voidStr->typeMeta->size);
  return res;
}

void Delete(voidString *voidStr) {
  assert(voidStr != NULL);
  if (voidStr->data != NULL)
    free(voidStr->data);
  free(voidStr);
}

void *GetI(voidString *voidStr, int i) {
  assert(validStr(voidStr));
  assert(i >= 0 && i < voidStr->len);
  return (char *)(voidStr->data) + i * (voidStr->typeMeta->size);
}
