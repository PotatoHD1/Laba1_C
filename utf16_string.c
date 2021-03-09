//
// Created by korna on 09.03.2021.
//

#include "void_string.c"
#include "utf16_string.h"
#include <assert.h>

typeMetadata *CreateUTF16Meta(int size) {
    return CreateTypeMeta(size, UTF16IsEqual, UTF16ToUTF8, UTF16ToUTF16, UTF16ToASCII, UTF16Lower, UTF16Higher);
}

int UTF16IsEqual(void *character1, void *character2) {

}

void *UTF16ToUTF8(void *character) {
    assert(0);
    return NULL;
}

void *UTF16ToUTF16(void *character) {
    return character;
}

void *UTF16ToASCII(void *character) {
    assert(0);
    return NULL;
}

void *UTF16Lower(void *character) {

}

void *UTF16Higher(void *character) {

}