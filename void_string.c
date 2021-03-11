//
// Created by korna on 08.03.2021.
//
#include "stdlib.h"
#include "void_string.h"
#include <string.h>
#include <assert.h>

voidString *CreateString(stringMetadata *stringMeta, int len) {
    assert(len > 0);
    assert(validStrMeta(stringMeta));
    voidString *res = (voidString *) calloc(1, sizeof(voidString));
    res->data = calloc(len, stringMeta->typeMeta->size);
    res->len = len;
    res->stringMeta = stringMeta;
    return res;
}

voidString *CreateStringFromCharArr(stringMetadata *stringMeta, int len, char *arr) {
    assert(len > 0);
    assert(validStrMeta(stringMeta));
    voidString *res = (voidString *) calloc(1, sizeof(voidString));
    res->data = calloc(len, stringMeta->typeMeta->size);
    memcpy(res->data, arr, len * stringMeta->typeMeta->size);
    res->len = len;
    res->stringMeta = stringMeta;
    return res;
}

typeMetadata *CreateTypeMeta(int size, int (*IsEqual)(void *, void *), void *(*ToUTF8)(void *),
                             void *(*ToUTF16)(void *), void *(*ToASCII)(void *), void *(*Lower)(void *),
                             void *(*Higher)(void *)) {
    typeMetadata *res = (typeMetadata *) calloc(1, sizeof(typeMetadata));
    res->size = size;
    res->IsEqual = IsEqual;
    res->ToUTF8 = ToUTF8;
    res->ToUTF16 = ToUTF16;
    res->ToASCII = ToASCII;
    res->Lower = Lower;
    res->Higher = Higher;

    return res;
}

stringMetadata *CreateStringMeta(typeMetadata *typeMetadata) {
    stringMetadata *res = (stringMetadata *) calloc(1, sizeof(stringMetadata));
    res->typeMeta = typeMetadata;
    res->GetI = GetI;
    res->Recode = Recode;
    res->StrStr = StrStr;
    res->Substring = Substring;
    res->Concat = Concat;
    res->Contains = Contains;
    res->CreateString = CreateString;
    res->CreateStringFromCharArr = CreateStringFromCharArr;
    res->Delete = Delete;
    return res;
}

int equalTypeMeta(typeMetadata *typeMetadata1, typeMetadata *typeMetadata2) {
    assert(validTypeMeta(typeMetadata1) && validTypeMeta(typeMetadata2));
    return typeMetadata1->size == typeMetadata2->size && typeMetadata1->IsEqual == typeMetadata2->IsEqual;
}

int validTypeMeta(typeMetadata *typeMetadata) {
    assert(typeMetadata != NULL);
    assert(typeMetadata->size > 0);
    assert(typeMetadata->Lower != NULL);
    assert(typeMetadata->IsEqual != NULL);
    assert(typeMetadata->ToASCII != NULL && typeMetadata->ToUTF16 != NULL && typeMetadata->ToUTF8 != NULL);
    return 1;
}

int validStrMeta(stringMetadata *stringMeta) {
    assert(stringMeta != NULL);
    assert(stringMeta->Recode != NULL);
    assert(stringMeta->Substring != NULL);
    assert(stringMeta->StrStr != NULL);
    assert(stringMeta->Concat != NULL);
    assert(stringMeta->CreateString != NULL);
    assert(stringMeta->GetI != NULL);
    assert(stringMeta->Delete != NULL);
    assert(validTypeMeta(stringMeta->typeMeta));
    return 1;
}

int validStr(voidString *voidStr) {
    assert(voidStr != NULL);
    assert(voidStr->data != NULL);
    assert(voidStr->len > 0);
    assert(validStrMeta(voidStr->stringMeta));
    return 1;
}

int equalStrMeta(voidString *voidStr1, voidString *voidStr2) {
    assert(validStr(voidStr1) && validStr(voidStr2));
    if (!equalTypeMeta(voidStr1->stringMeta->typeMeta, voidStr2->stringMeta->typeMeta))
        return 0;
    return voidStr1->stringMeta->Recode == voidStr2->stringMeta->Recode &&
           voidStr1->stringMeta->Substring == voidStr2->stringMeta->Substring &&
           voidStr1->stringMeta->StrStr == voidStr2->stringMeta->StrStr &&
           voidStr1->stringMeta->Concat == voidStr2->stringMeta->Concat &&
           voidStr1->stringMeta->CreateString == voidStr2->stringMeta->CreateString &&
           voidStr1->stringMeta->GetI == voidStr2->stringMeta->GetI &&
           voidStr1->stringMeta->Delete == voidStr2->stringMeta->Delete;
}


voidString *Concat(voidString *voidStr1, voidString *voidStr2) {
    assert(equalStrMeta(voidStr1, voidStr2));
    voidString *res = CreateString(voidStr1->stringMeta, voidStr1->len + voidStr2->len);
    memcpy(res->data, voidStr1->data, voidStr1->len * voidStr1->stringMeta->typeMeta->size);
    memcpy(GetI(res, voidStr1->len), voidStr2->data,
           voidStr2->len * voidStr2->stringMeta->typeMeta->size);
    return res;
}

voidString *Recode(void *(*func)(void *), voidString *voidStr, stringMetadata *newStringMeta) {
    assert(func != NULL && validStr(voidStr));
    voidString *res = CreateString(newStringMeta, voidStr->len);
    for (int i = 0; i < voidStr->len; ++i) {
        void *tmp = func(GetI(voidStr, i));
        assert(tmp != NULL);
        memcpy(GetI(res, i), tmp, voidStr->stringMeta->typeMeta->size);
        free(tmp);
    }
    return res;
}

int Contains(voidString *voidStr1, voidString *voidStr2, int start, int n) {
    assert(equalStrMeta(voidStr1, voidStr2));
    assert(start >= 0 && n >= 0);
    if (voidStr2->len > (voidStr1->len - start) || voidStr2->len < n)
        return 0;

    for (int i = start; i < start + n; ++i)
        if (!voidStr1->stringMeta->typeMeta->IsEqual(GetI(voidStr1, i), GetI(voidStr1, i - start)))
            return 0;
    return 1;
}

void *StrStr(voidString *voidStr1, voidString *voidStr2, int lower) {
    assert(equalStrMeta(voidStr1, voidStr2));
    assert(lower == 0 || lower == 1);
    if (lower) {
        voidStr1 = voidStr1->stringMeta->Recode(voidStr1->stringMeta->typeMeta->Lower, voidStr1, voidStr1->stringMeta);
        voidStr2 = voidStr2->stringMeta->Recode(voidStr2->stringMeta->typeMeta->Lower, voidStr2, voidStr2->stringMeta);
    }
    int start = 0;
    while (start <= voidStr1->len) {
        if (Contains(voidStr1, voidStr2, start, voidStr1->len))
            return GetI(voidStr1, start);
        start++;
    }

    return NULL;
}


voidString *Substring(int a, int b, voidString *voidStr) {
    assert(validStr(voidStr));
    voidString *res = CreateString(voidStr->stringMeta, b - a + 1);
    res->data = memcpy(res->data, GetI(voidStr, a),
                       b * voidStr->stringMeta->typeMeta->size);
    return res;
}


void Delete(voidString *voidStr) {
    assert(voidStr != NULL);
    if (voidStr->data != NULL)
        free(voidStr->data);
    free(voidStr);
}

void *GetI(voidString *voidStr, int i) {
    assert(validStr(voidStr));
    assert(i >= 0 && i < voidStr->len);
    return (char *) (voidStr->data) + i * (voidStr->stringMeta->typeMeta->size);
}
