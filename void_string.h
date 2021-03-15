//
// Created by korna on 27.02.2021.
//

#ifndef LABA1_VOID_STRING_H
#define LABA1_VOID_STRING_H
#include <stdbool.h>
typedef struct voidString voidString;
typedef struct typeMetadata typeMetadata;

struct typeMetadata {
  int size;

  void (*SetLocale)(char **);

  bool (*IsEqual)(void *, void *, char **);

  void *(*ToUTF8)(void *, char **);

  void *(*ToUNICODE)(void *, char **);

  void *(*ToASCII)(void *, char **);

  void *(*Lower)(void *, char **);

  void *(*Higher)(void *, char **);

  void (*Print)(void *, char **);

  void *(*PreprocessStr)(void *, char **);
};

struct voidString {
  void *data;
  int len;
  typeMetadata *typeMeta;
};

voidString *CreateFromCharArray(typeMetadata *, int, char *, char **);

voidString *Concat(voidString *, voidString *, char **);

voidString *Substring(int, int, voidString *, char **);

void Delete(voidString *, char **);

void *GetI(voidString *, int, char **);

voidString *CreateString(typeMetadata *, int, char **);

bool equalTypeMeta(voidString *, voidString *, char **);

voidString *Recode(void *(*)(void *, char **), voidString *, typeMetadata *,
                   char **);

int StrStr(voidString *, voidString *, bool, char **);

bool Contains(voidString *, voidString *, int, int, char **);

bool validTypeMeta(typeMetadata *, char **);

bool validStr(voidString *, char **);

typeMetadata *
CreateTypeMeta(int, bool (*)(void *, void *, char **),
               void *(*)(void *, char **), void *(*)(void *, char **),
               void *(*)(void *, char **), void *(*)(void *, char **),
               void *(*)(void *, char **), void (*)(char **),
               void (*)(void *, char **), void *(*)(void *, char **), char **);

void Map(void *(*)(void *, char **), voidString *, char **);

void ToLower(voidString *, char **);

void ToHigher(voidString *, char **);

void AddToLog(char **, char[]);

void RemoveFromLog(char **);

bool IsLogError(char **);

bool StrIsEqual(voidString *, voidString *, char **);

#endif // LABA1_VOID_STRING_H
