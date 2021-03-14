//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UTF8_STRING_H
#define LABA1_UTF8_STRING_H

int UTF8IsEqual(void *, void *, char **);

void *UTF8ToUTF8(void *, char **);

void *UTF8ToUNICODE(void *, char **);

void *UTF8ToASCII(void *, char **);

void *UTF8Lower(void *, char **);

void *UTF8Higher(void *, char **);

int UTF8IsValid(void *, char **);

typeMetadata *CreateUTF8Meta(char **);

int UTF8GetLen(void *, char **);

void SetUTF8Locale(char **);

void *ScanUTF8(char **);

void PrintUTF8(void *, char **);

void SetUTF8Locale(char **);

#endif //LABA1_UTF8_STRING_H
