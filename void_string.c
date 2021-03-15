//
// Created by korna on 08.03.2021.
//
#include "void_string.h"
#include "stdlib.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

voidString *CreateString(typeMetadata *typeMeta, int len, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "CreateString");
  if (len <= 0) {
    AddToLog(errorlog, "Error: len <= 0~");
    return NULL;
  }
  validTypeMeta(typeMeta, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  voidString *res = (voidString *)calloc(1, sizeof(voidString));
  res->data = calloc(len, typeMeta->size + 1);
  res->len = len + 1;
  res->typeMeta = typeMeta;
  RemoveFromLog(errorlog);
  return res;
}
void AddToLog(char **errorlog, char text[]) {
  int len = strlen(*errorlog);
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

bool IsLogError(char **errorlog) {
  int count = 0;
  int len = strlen(*errorlog);
  if (len > 0)
    if ((*errorlog)[len - 1] == '~')
      return true;
  return false;
}
voidString *CreateFromCharArray(typeMetadata *typeMeta, int len, char *arr,
                                char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "CreateFromCharArray");
  if (len <= 0) {
    AddToLog(errorlog, "Error: len <= 0~");
    return NULL;
  }
  validTypeMeta(typeMeta, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  char *data = typeMeta->PreprocessStr(arr, errorlog);
  if (IsLogError(errorlog))
    return NULL;
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
    void (*Print)(void *, char **), void *(*PreprocessStr)(void *, char **),
    char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "CreateTypeMeta");
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
  res->PreprocessStr = PreprocessStr;
  RemoveFromLog(errorlog);
  return res;
}

bool equalTypeMeta(voidString *voidString1, voidString *voidString2,
                   char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "equalTypeMeta");
  validStr(voidString1, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  validStr(voidString2, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  RemoveFromLog(errorlog);
  return voidString1->typeMeta->size == voidString2->typeMeta->size &&
         voidString1->typeMeta->SetLocale == voidString2->typeMeta->SetLocale &&
         voidString1->typeMeta->IsEqual == voidString2->typeMeta->IsEqual &&
         voidString1->typeMeta->ToUTF8 == voidString2->typeMeta->ToUTF8 &&
         voidString1->typeMeta->ToUNICODE == voidString2->typeMeta->ToUNICODE &&
         voidString1->typeMeta->ToASCII == voidString2->typeMeta->ToASCII &&
         voidString1->typeMeta->Lower == voidString2->typeMeta->Lower &&
         voidString1->typeMeta->Higher == voidString2->typeMeta->Higher &&
         voidString1->typeMeta->Print == voidString2->typeMeta->Print;
}

bool validTypeMeta(typeMetadata *typeMetadata, char **errorlog) {
  AddToLog(errorlog, "validTypeMeta");
  if (typeMetadata == NULL) {
    AddToLog(errorlog, "Error: typeMetadata == NULL~");
    return NULL;
  }
  if (typeMetadata->size <= 0) {
    AddToLog(errorlog, "Error: typeMetadata->size <= 0~");
    return NULL;
  }
  if (typeMetadata->SetLocale == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->SetLocale == NULL~");
    return NULL;
  }
  if (typeMetadata->IsEqual == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->IsEqual == NULL~");
    return NULL;
  }
  if (typeMetadata->ToUTF8 == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->ToUTF8 == NULL~");
    return NULL;
  }
  if (typeMetadata->ToUNICODE == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->ToUNICODE == NULL~");
    return NULL;
  }
  if (typeMetadata->ToASCII == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->ToASCII == NULL~");
    return NULL;
  }
  if (typeMetadata->Lower == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->Lower  == NULL~");
    return NULL;
  }
  if (typeMetadata->Higher == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->Higher == NULL~");
    return NULL;
  }
  if (typeMetadata->Print == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->Print == NULL~");
    return NULL;
  }
  if (typeMetadata->PreprocessStr == NULL) {
    AddToLog(errorlog, "Error: typeMetadata->PreprocessStr == NULL~");
    return NULL;
  }
  RemoveFromLog(errorlog);
  return true;
}

bool validStr(voidString *voidStr, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "validStr");
  if (voidStr == NULL) {
    AddToLog(errorlog, "Error: voidStr == NULL~");
    return NULL;
  }
  if (voidStr->data == NULL) {
    AddToLog(errorlog, "Error: voidStr->data == NULL~");
    return NULL;
  }
  if (voidStr->len <= 0) {
    AddToLog(errorlog, "Error: voidStr->len <= 0~");
    return NULL;
  }
  validTypeMeta(voidStr->typeMeta, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  RemoveFromLog(errorlog);
  return true;
}

voidString *Concat(voidString *voidStr1, voidString *voidStr2,
                   char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "Concat");
  if (!equalTypeMeta(voidStr1, voidStr2, errorlog)) {
    AddToLog(errorlog, "Error: not equal type meta~");
    return NULL;
  }
  voidString *res = CreateString(voidStr1->typeMeta,
                                 voidStr1->len + voidStr2->len - 2, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  memcpy(res->data, voidStr1->data,
         (voidStr1->len - 1) * voidStr1->typeMeta->size);
  void * tmp = GetI(res, voidStr1->len - 1, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  memcpy(tmp, voidStr2->data,
         (voidStr2->len - 1) * voidStr2->typeMeta->size);
  if (IsLogError(errorlog))
    return NULL;
  RemoveFromLog(errorlog);
  return res;
}

voidString *Recode(void *(*func)(void *, char **), voidString *voidStr,
                   typeMetadata *newtypeMeta, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "Recode");
  if (func == NULL) {
    AddToLog(errorlog, "Error: func == NULL~");
    return NULL;
  }
  if (IsLogError(errorlog))
    return NULL;
  validStr(voidStr, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  voidString *res = CreateString(newtypeMeta, voidStr->len - 1, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  for (int i = 0; i < voidStr->len; ++i) {
    void *tmp = func(GetI(voidStr, i, errorlog), errorlog);
    if (IsLogError(errorlog))
      return NULL;
    if (tmp == NULL) {
      AddToLog(errorlog, "Error: func returned NULL~");
      return NULL;
    }
    void * tmp1 = GetI(res, i, errorlog);
    if (IsLogError(errorlog))
      return NULL;
    memcpy(tmp1, tmp, voidStr->typeMeta->size);
    if (IsLogError(errorlog))
      return NULL;
    free(tmp);
  }
  RemoveFromLog(errorlog);
  return res;
}

bool Contains(voidString *voidStr1, voidString *voidStr2, int start, int n,
              char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "Contains");
  if (!equalTypeMeta(voidStr1, voidStr2, errorlog)) {
    AddToLog(errorlog, "Error: Not equal type meta~");
    return NULL;
  }
  if (IsLogError(errorlog))
    return NULL;
  if (!(start >= 0 && n >= 0)) {
    AddToLog(errorlog, "Error: start < 0 or n < 0~");
    return NULL;
  }
  if (voidStr2->len > (voidStr1->len - start) || voidStr2->len < n) {
    RemoveFromLog(errorlog);
    return false;
  }

  for (int i = start; i < start + n; ++i)
    if (!voidStr1->typeMeta->IsEqual(GetI(voidStr1, i, errorlog),
                                     GetI(voidStr1, i - start, errorlog),
                                     errorlog)) {
      if (IsLogError(errorlog))
        return NULL;
      RemoveFromLog(errorlog);
      return false;
    }
  RemoveFromLog(errorlog);
  return true;
}

void Map(void *(*func)(void *, char **), voidString *voidStr, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "Map");
  if (func == NULL) {
    AddToLog(errorlog, "Error: func == NULL~");
    return;
  }
  validStr(voidStr, errorlog);
  if (IsLogError(errorlog))
    return;
  for (int i = 0; i < voidStr->len; ++i) {
    void *tmp = func(GetI(voidStr, i, errorlog), errorlog);
    if (tmp == NULL) {
      AddToLog(errorlog, "Error: tmp == NULL~");
      return;
    }
    void * tmp1 = GetI(voidStr, i, errorlog);
    if (IsLogError(errorlog))
      return;
    memcpy(tmp1, tmp, voidStr->typeMeta->size);
    free(tmp);
  }
  RemoveFromLog(errorlog);
}

void ToLower(voidString *str, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "ToLower");
  Map(str->typeMeta->Lower, str, errorlog);
  if (IsLogError(errorlog))
    return;
  RemoveFromLog(errorlog);
}

void ToHigher(voidString *str, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "ToHigher");
  Map(str->typeMeta->Higher, str, errorlog);
  if (IsLogError(errorlog))
    return;
  RemoveFromLog(errorlog);
}

void PrintStr(voidString *str, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "PrintStr");
  str->typeMeta->SetLocale(errorlog);
  if (IsLogError(errorlog))
    return;
  for (int i = 0; i < str->len; ++i) {
    str->typeMeta->Print(GetI(str, i, errorlog), errorlog);
    if (IsLogError(errorlog))
      return;
  }
  printf("\n");
  RemoveFromLog(errorlog);
}

void *StrStr(voidString *voidStr1, voidString *voidStr2, int lower,
             char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "StrStr");
  if (!equalTypeMeta(voidStr1, voidStr2, errorlog)) {
    AddToLog(errorlog, "Error: not equal type meta~");
    return NULL;
  }
  if (!(lower == 0 || lower == 1)) {
    AddToLog(errorlog, "Error: lower is not bool~");
    return NULL;
  }
  if (lower) {
    ToLower(voidStr1, errorlog);
    if (IsLogError(errorlog))
      return NULL;
    ToLower(voidStr2, errorlog);
    if (IsLogError(errorlog))
      return NULL;
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

voidString *Substring(int i, int j, voidString *voidStr, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "Substring");

  validStr(voidStr, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  if (i < 0) {
    AddToLog(errorlog, "Error: i < 0~");
    return NULL;
  }
  if (j < i) {
    AddToLog(errorlog, "Error: j < i~");
    return NULL;
  }
  voidString *res = CreateString(voidStr->typeMeta, j - i + 1, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  void * tmp = GetI(voidStr, i, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  res->data = memcpy(res->data, tmp,
                     (j - i + 1) * voidStr->typeMeta->size);
  RemoveFromLog(errorlog);
  return res;
}

void Delete(voidString *voidStr, char **errorlog) {
  if (IsLogError(errorlog))
    return;
  AddToLog(errorlog, "Delete");
  if (voidStr == NULL) {
    AddToLog(errorlog, "Error: voidStr == NULL~");
    return;
  }
  if (voidStr->data != NULL) {
    voidStr->data = realloc(voidStr->data, 1);
    free(voidStr->data);
  }
  free(voidStr);
  RemoveFromLog(errorlog);
}

void *GetI(voidString *voidStr, int i, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "GetI");
  validStr(voidStr, errorlog);
  if (IsLogError(errorlog))
    return NULL;
  if (i < 0) {
    AddToLog(errorlog, "Error: i < 0~");
    return NULL;
  }
  if (i >= voidStr->len) {
    AddToLog(errorlog, "Error: i >= voidStr->len~");
    return NULL;
  }
  RemoveFromLog(errorlog);
  return (char *)(voidStr->data) + i * (voidStr->typeMeta->size);
}

bool StrIsEqual(voidString *a, voidString *b, char **errorlog) {
  if (IsLogError(errorlog))
    return NULL;
  AddToLog(errorlog, "StrIsEqual");
  if (a->len != b->len) {
    RemoveFromLog(errorlog);
    return false;
  }
  for (int i = 0; i < a->len; ++i) {
    if (!a->typeMeta->IsEqual(GetI(a, i, errorlog), GetI(b, i, errorlog),
                              errorlog)) {
      if (IsLogError(errorlog))
        return NULL;
      RemoveFromLog(errorlog);
      return false;
    }
  }
  RemoveFromLog(errorlog);
  return true;
}