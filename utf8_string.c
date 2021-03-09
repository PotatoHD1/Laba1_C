//
// Created by korna on 09.03.2021.
//

#include "void_string.c"
#include "utf8_string.h"

typeMetadata *CreateUTF8Meta(int size) {
    return CreateTypeMeta(size, UTF8IsEqual, UTF8ToUTF8, UTF8ToUTF16, UTF8ToASCII, UTF8Lower);
}

int UTF8IsEqual(void *character1, void *character2) {

}

void *UTF8ToUTF8(void *character) {
    return character;
}

void *UTF8ToUTF16(void *character) {

}

void *UTF8ToASCII(void *character) {

}

void *UTF8Lower(void *character) {

}
