//
// Created by korna on 09.03.2021.
//

#include "void_string.c"
#include "ascii_string.h"

typeMetadata *CreateASCIIMeta(int size) {
    return CreateTypeMeta(size, ASCIIIsEqual, ASCIIToUTF8, ASCIIToUTF16, ASCIIToASCII, ASCIILower);
}

int ASCIIIsEqual(void *character1, void *character2) {

}

void *ASCIIToUTF8(void *character) {

}

void *ASCIIToUTF16(void *character) {

}

void *ASCIIToASCII(void *character) {
    return character;
}

void *ASCIILower(void *character) {

}
