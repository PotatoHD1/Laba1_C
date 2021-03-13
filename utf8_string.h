//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UTF8_STRING_H
#define LABA1_UTF8_STRING_H

int UTF8IsEqual(void *, void *);

void *UTF8ToUTF8(void *);

void *UTF8ToUNICODE(void *);

void *UTF8ToASCII(void *);

void *UTF8Lower(void *);

void *UTF8Higher(void *);

int UTF8IsValid(void *);

typeMetadata *CreateUTF8Meta(int size);

int UTF8GetLen(void *);

#endif //LABA1_UTF8_STRING_H
