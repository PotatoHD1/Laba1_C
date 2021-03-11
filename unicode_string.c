//
// Created by korna on 09.03.2021.
//

#include "void_string.c"
#include "unicode_string.h"
#include <assert.h>

typeMetadata *CreateUNICODEMeta(int size) {
    return CreateTypeMeta(size, UNICODEIsEqual, UNICODEToUTF8, UNICODEToUNICODE, UNICODEToASCII, UNICODELower,
                          UNICODEHigher);
}

int UNICODEIsEqual(void *character1, void *character2) {
    assert(UNICODEIsValid(character1) && UNICODEIsValid(character2));
    return *(unsigned char *) character1 == *(unsigned char *) character2;
}

void *UNICODEToUTF8(void *character) {
    assert(UNICODEIsValid(character));
    unsigned char *res;
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

void *UNICODEToUNICODE(void *character) {
    return character;
}

void *UNICODEToASCII(void *character) {
    assert(0);
    return NULL;
}


void *UNICODELower(void *character) {
    unsigned char *res = (unsigned char *) calloc(1, 1);
    if (*(char *) character >= 'A' && *(char *) character <= 'Z')
        *res = 'a' - 'A' + *(unsigned char *) character;
    else if (*(unsigned char *) character >= 128 && *(unsigned char *) character <= 143)
        *res = 160 - 128 + *(unsigned char *) character;
    else if (*(unsigned char *) character >= 144 && *(unsigned char *) character <= 159)
        *res = 224 - 144 + *(unsigned char *) character;
    else if (*(unsigned char *) character == 240)
        *res = 241;
    else
        *res = *(unsigned char *) character;
    return res;
}

void *UNICODEHigher(void *character) {
    unsigned char *res = (unsigned char *) calloc(1, 1);
    if (*(char *) character >= 'a' && *(char *) character <= 'z')
        *res = 'A' - 'a' + *(unsigned char *) character;
    else if (*(unsigned char *) character >= 160 && *(unsigned char *) character <= 175)
        *res = 128 - 160 + *(unsigned char *) character;
    else if (*(unsigned char *) character >= 224 && *(unsigned char *) character <= 239)
        *res = 144 - 224 + *(unsigned char *) character;
    else if (*(unsigned char *) character == 241)
        *res = 240;
    else
        *res = *(unsigned char *) character;
    return res;
}