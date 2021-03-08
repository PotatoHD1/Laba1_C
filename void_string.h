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

    int (*IsEqual)(void *, void *);

    void *(*Lower)(void *);
};

struct stringMetadata {
    typeMetadata *typeMeta;

    voidString *(*Concat)(voidString *, voidString *);

    voidString *(*Substring)(int, int, voidString *);

    void *(*StrStr)(voidString *, voidString *, int);

    voidString *(*Recode)(void *(*)(void *), voidString *);

    voidString *(*CreateString)(stringMetadata *, int);

    void *(*GetI)(voidString *, int);

    void (*Delete)(voidString *);

    int (*Contains)(voidString *, voidString *, int, int);
};

struct voidString {
    void *data;
    int len;
    stringMetadata *stringMeta;
};

voidString *Concat(voidString *, voidString *);

voidString *Substring(int, int, voidString *);

void *Delete(voidString *);

void *GetI(voidString *, int);

voidString *CreateString(stringMetadata *, int);

int equalStrMeta(stringMetadata *, stringMetadata *);

int equalTypeMeta(typeMetadata *, typeMetadata *);

voidString *Recode(void *(*)(void *), voidString *);

void *StrStr(voidString *, voidString *, int);

int Contains(voidString *, voidString *, int, int);

#endif //LABA1_VOID_STRING_H
