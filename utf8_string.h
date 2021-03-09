//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UTF8_STRING_H
#define LABA1_UTF8_STRING_H

#include "void_string.с"

int IsEqual(void *, void *);

void *ToUTF8(void *);

void *ToUTF16(void *);

void *ToASCII(void *);

void *Lower(void *);

typeMetadata *CreateUTF8Meta(int size);

#endif //LABA1_UTF8_STRING_H
