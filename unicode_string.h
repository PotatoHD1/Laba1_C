//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UNICODE_STRING_H
#define LABA1_UNICODE_STRING_H

bool UNICODEIsEqual(void *, void *, char **);

void *UNICODEToUTF8(void *, char **);

void *UNICODEToUNICODE(void *, char **);

void *UNICODEToASCII(void *, char **);

void *UNICODELower(void *, char **);

void *UNICODEHigher(void *, char **);

bool UNICODEIsValid(void *, char **);

typeMetadata *CreateUNICODEMeta(char **);

void SetUNICODELocale(char **);

void *ScanUNICODE(char **);

void PrintUNICODE(void *, char **);

void *PreprocessUNICODEStr(void *, char **);

#endif // LABA1_UNICODE_STRING_H
