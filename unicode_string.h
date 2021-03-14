//
// Created by korna on 09.03.2021.
//

#ifndef LABA1_UNICODE_STRING_H
#define LABA1_UNICODE_STRING_H

int UNICODEIsEqual(void *, void *);

void *UNICODEToUTF8(void *);

void *UNICODEToUNICODE(void *);

void *UNICODEToASCII(void *);

void *UNICODELower(void *);

void *UNICODEHigher(void *);

int UNICODEIsValid(void *);

typeMetadata *CreateUNICODEMeta();

void SetUNICODELocale();

void *ScanUNICODE();

void PrintUNICODE(void *);

void SetUNICODELocale();

#endif //LABA1_UNICODE_STRING_H
