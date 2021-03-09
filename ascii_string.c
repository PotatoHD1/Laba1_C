//
// Created by korna on 09.03.2021.
//

#include "void_string.c"
#include "ascii_string.h"
#include <assert.h>

typeMetadata *CreateASCIIMeta(int size) {
    return CreateTypeMeta(size, ASCIIIsEqual, ASCIIToUTF8, ASCIIToUTF16, ASCIIToASCII, ASCIILower, ASCIIHigher);
}

int ASCIIIsValid(void *character) {
    assert(character != NULL);
    return 1;
}

int ASCIIIsEqual(void *character1, void *character2) {
    assert(ASCIIIsValid(character1) && ASCIIIsValid(character2));
    return *(unsigned char *) character1 == *(unsigned char *) character2;
}

void *ASCIIToUTF8(void *character) {
    assert(ASCIIIsValid(character));
    char *res;
    if (*(unsigned char *) character < 128) {
        res = calloc(1, 1);
        *(res) = *(unsigned char *) character;
    } else {
        res = calloc(1, 2);
        *(res) = 0xC0 | (*(unsigned char *) character >> 6);
        *(res + 1) = 0x80 | (*(unsigned char *) character & 0x3f);
    }
    return res;
}

void *ASCIIToUnicode(void *character) {
    assert(ASCIIIsValid(character));
    char *res;
    res = calloc(1, 1);
    *(res) = *(unsigned char *) character;
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

