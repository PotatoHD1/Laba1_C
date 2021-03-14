//
// Created by korna on 09.03.2021.
//

#include "ascii_string.h"
#include <assert.h>

typeMetadata *CreateASCIIMeta(int size) {
    return CreateTypeMeta(size, ASCIIIsEqual, ASCIIToUTF8, ASCIIToUNICODE, ASCIIToASCII, ASCIILower, ASCIIHigher,
                          SetASCIILocale, ScanASCII, PrintASCII);
}

stringMetadata *CreateASCIIStringMeta() {
    return CreateStringMeta(CreateASCIIMeta(sizeof(char)));
}

int ASCIIIsValid(void *character) {
    assert(character != NULL);
    return 1;
}

int ASCIIIsEqual(void *character1, void *character2) {
    assert(ASCIIIsValid(character1) && ASCIIIsValid(character2));
    return *(char *) character1 == *(char *) character2;
}

void *ASCIIToUTF8(void *character) {
    assert(ASCIIIsValid(character));
    char *res;
    res = calloc(1, 1);
    *(res) = *(char *) character;
    return res;
}

void *ASCIIToUNICODE(void *character) {
    assert(ASCIIIsValid(character));
    char *res;
    res = calloc(1, 1);
    *(res) = *(char *) character;
    return res;
}

void *ASCIIToASCII(void *character) {
    return character;
}

void *ASCIILower(void *character) {
    char *res = (char *) calloc(1, 1);
    if (*(char *) character >= 'A' && *(char *) character <= 'Z')
        *res = 'a' - 'A' + *(char *) character;
    else
        *res = *(char *) character;
    return res;
}

void *ASCIIHigher(void *character) {
    char *res = (char *) calloc(1, 1);
    if (*(char *) character >= 'a' && *(char *) character <= 'z')
        *res = 'A' - 'a' + *(char *) character;
    else
        *res = *(char *) character;
    return res;
}

