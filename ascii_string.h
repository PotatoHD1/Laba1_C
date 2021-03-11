//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_ASCII_STRING_H
#define LABA1_ASCII_STRING_H

#include "void_string.h"

int ASCIIIsEqual(void *, void *);

void *ASCIIToUTF8(void *);

void *ASCIIToUNICODE(void *);

void *ASCIIToASCII(void *);

void *ASCIILower(void *);

void *ASCIIHigher(void *);

int ASCIIIsValid(void *);

typeMetadata *CreateASCIIMeta(int size);

#endif //LABA1_ASCII_STRING_H
