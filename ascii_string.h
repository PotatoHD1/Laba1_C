//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_ASCII_STRING_H
#define LABA1_ASCII_STRING_H

bool ASCIIIsEqual(void *, void *, char **);

void *ASCIIToUTF8(void *, char **);

void *ASCIIToUNICODE(void *, char **);

void *ASCIIToASCII(void *, char **);

void *ASCIILower(void *, char **);

void *ASCIIHigher(void *, char **);

bool ASCIIIsValid(void *, char **);

typeMetadata *CreateASCIIMeta(char **);

void SetASCIILocale(char **);

void *ScanASCII(char **);

void PrintASCII(void *, char **);

void *PreprocessASCIIStr(void *, char **);

#endif // LABA1_ASCII_STRING_H
