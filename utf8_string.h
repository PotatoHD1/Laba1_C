//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UTF8_STRING_H
#define LABA1_UTF8_STRING_H

#include "void_string.h"

int UTF8IsEqual(void *, void *);

void *UTF8ToUTF8(void *);

void *UTF8ToUTF16(void *);

void *UTF8ToASCII(void *);

void *UTF8Lower(void *);

typeMetadata *CreateUTF8Meta(int size);

#endif //LABA1_UTF8_STRING_H
