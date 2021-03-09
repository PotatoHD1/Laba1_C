//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UTF16_STRING_H
#define LABA1_UTF16_STRING_H

#include "void_string.h"

int UTF16IsEqual(void *, void *);

void *UTF16ToUTF8(void *);

void *UTF16ToUTF16(void *);

void *UTF16ToASCII(void *);

void *UTF16Lower(void *);

void *UTF16Higher(void *);

int UTF16IsValid(void *);

typeMetadata *CreateUTF16Meta(int size);

#endif //LABA1_UTF16_STRING_H
