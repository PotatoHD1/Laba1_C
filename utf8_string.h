//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UTF8_STRING_H
#define LABA1_UTF8_STRING_H

bool UTF8IsEqual(void *, void *, char **);

void *UTF8ToUTF8(void *, char **);

void *UTF8ToUNICODE(void *, char **);

void *UTF8ToASCII(void *, char **);

void *UTF8Lower(void *, char **);

void *UTF8Higher(void *, char **);

bool UTF8IsValid(void *, char **);

typeMetadata *CreateUTF8Meta(char **);

int UTF8GetLen(void *, char **);

void SetUTF8Locale(char **);

void PrintUTF8(void *, char **);

void *PreprocessUTF8Str(void *, char **);

#endif // LABA1_UTF8_STRING_H
