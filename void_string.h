//
// Created by korna on 27.02.2021.
//

#ifndef LABA1_VOID_STRING_H
#define LABA1_VOID_STRING_H
typedef struct voidString voidString;
typedef struct typeMetadata typeMetadata;

struct typeMetadata {
    int size;

    void (*SetLocale)();

    int (*IsEqual)(void *, void *);

    void *(*ToUTF8)(void *);

    void *(*ToUNICODE)(void *);

    void *(*ToASCII)(void *);

    void *(*Lower)(void *);

    void *(*Higher)(void *);

    void *(*Scan)();

    void (*Print)(void *);
};

struct voidString {
    void *data;
    int len;
    typeMetadata *typeMeta;
};

voidString *CreateFromCharArray(typeMetadata *, int, char *);

voidString *Concat(voidString *, voidString *);

voidString *Substring(int, int, voidString *);

void Delete(voidString *);

void *GetI(voidString *, int);

voidString *CreateString(typeMetadata *, int);

int equalTypeMeta(voidString *, voidString *);

voidString *Recode(void *(*)(void *), voidString *, typeMetadata *);

void *StrStr(voidString *, voidString *, int);

int Contains(voidString *, voidString *, int, int);

int validTypeMeta(typeMetadata *);

int validStr(voidString *);

typeMetadata *CreateTypeMeta(int, int (*)(void *, void *), void *(*)(void *), void *(*)(void *), void *(*)(void *),
                             void *(*)(void *), void *(*)(void *), void(*)(), void *(*)(), void (*)(void *));

void Map(void *(*)(void *), voidString *);

void ToLower(voidString *);

void ToHigher(voidString *);

#endif //LABA1_VOID_STRING_H
