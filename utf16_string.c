//
// Created by korna on 09.03.2021.
//

#include "void_string.c"
#include "utf16_string.h"

typeMetadata *CreateUTF16Meta(int size) {
    return CreateTypeMeta(size, UTF16IsEqual, UTF16ToUTF8, UTF8ToUTF16, UTF8ToASCII, UTF8Lower);
}

int UTF16IsEqual(void *character1, void *character2) {

}

void *UTF16ToUTF8(void *character) {

}

void *UTF16ToUTF16(void *character) {
    return character;
}

void *UTF16ToASCII(void *character) {

}

void *UTF16Lower(void *character) {

}