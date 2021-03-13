//
// Created by korna on 09.03.2021.
//
#include "utf8_string.h"
#include <assert.h>

typeMetadata *CreateUTF8Meta(int size) {
    return CreateTypeMeta(size, UTF8IsEqual, UTF8ToUTF8, UTF8ToUNICODE, UTF8ToASCII, UTF8Lower, UTF8Higher);
}

int UTF8IsValid(void *character) {
    assert(character != NULL);
    assert(((unsigned char *) character)[0] < 128 ||
           (((unsigned char *) character)[0] >= 128 && ((unsigned char *) character)[0] <= 191));
    return 1;
}


int UTF8IsEqual(void *character1, void *character2) {
    int len1 = UTF8GetLen(character1);
    int len2 = UTF8GetLen(character2);
    if (len1 != len2)
        return 0;

}

int UTF8GetLen(void *character) {
    int res = 1;
    if (*((unsigned char *) character) > 128)
        while ((*((unsigned char *) character + res) >= 128 && *((unsigned char *) character + res) <= 191) &&
               res < 4)
            res++;
    return res;
}

void *UTF8ToUTF8(void *character) {
    return character;
}

void *UTF8ToUNICODE(void *character) {
    assert(0);
    return NULL;
}

void *UTF8ToASCII(void *character) {
    assert(0);
    return NULL;
}

void *UTF8Lower(void *character) {

}

void *UTF8Higher(void *character) {

}
