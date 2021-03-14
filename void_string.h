//
// Created by korna on 27.02.2021.
//

#ifndef LABA1_VOID_STRING_H
#define LABA1_VOID_STRING_H
typedef struct voidString voidString;
typedef struct typeMetadata typeMetadata;
typedef struct stringMetadata stringMetadata;

struct typeMetadata {
    size_t size;

    void (*SetLocale)();

    int (*IsEqual)(void *, void *);

    void *(*ToUTF8)(void *);

    void *(*ToUTF16)(void *);

    void *(*ToASCII)(void *);

    void *(*Lower)(void *);

    void *(*Higher)(void *);

    void *(*Scan)();

    void (*Print)(void *);
};

struct stringMetadata {
    typeMetadata *typeMeta;

    voidString *(*Concat)(voidString *, voidString *);

    voidString *(*Substring)(int, int, voidString *);

    void *(*StrStr)(voidString *, voidString *, int);

    voidString *(*Recode)(void *(*)(void *), voidString *, stringMetadata *);

    voidString *(*CreateString)(stringMetadata *, int);

    voidString *(*CreateStringFromCharArr)(stringMetadata *, int, char *);

    void *(*GetI)(voidString *, int);

    void (*Delete)(voidString *);

    int (*Contains)(voidString *, voidString *, int, int);

    void (*Map)(void *(*)(void *), voidString *);

    void (*ToLower)(voidString *);

    void (*ToHigher)(voidString *);

};

struct voidString {
    void *data;
    int len;
    stringMetadata *stringMeta;
};

voidString *CreateFromCharArray(stringMetadata *, int, char *);

voidString *Concat(voidString *, voidString *);

voidString *Substring(int, int, voidString *);

void Delete(voidString *);

void *GetI(voidString *, int);

voidString *CreateString(stringMetadata *, int);

int equalTypeMeta(typeMetadata *, typeMetadata *);

voidString *Recode(void *(*)(void *), voidString *, stringMetadata *);

void *StrStr(voidString *, voidString *, int);

int Contains(voidString *, voidString *, int, int);

int validStrMeta(stringMetadata *);

int validTypeMeta(typeMetadata *);

int validStr(voidString *);

int equalStrMeta(voidString *, voidString *);

typeMetadata *CreateTypeMeta(int, int (*)(void *, void *), void *(*)(void *), void *(*)(void *), void *(*)(void *),
                             void *(*)(void *), void *(*)(void *), void(*)(), void *(*)(), void (*)(void *));

void Map(void *(*)(void *), voidString *);

void ToLower(voidString *);

void ToHigher(voidString *);

#endif //LABA1_VOID_STRING_H
