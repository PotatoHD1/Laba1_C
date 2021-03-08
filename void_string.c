//
// Created by korna on 08.03.2021.
//
#include "stdlib.h"
#include "void_string.h"
#include <string.h>
#include <assert.h>

voidString *CreateString(stringMetadata *stringMeta, int len) {
    voidString *res = (voidString *) calloc(1, sizeof(voidString));
    res->data = calloc(len, stringMeta->typeMeta->size);
    res->len = len;
    res->stringMeta = stringMeta;
    return res;
}

int equalTypeMeta(typeMetadata *typeMetadata1, typeMetadata *typeMetadata2) {
    assert(typeMetadata1 != NULL && typeMetadata2 != NULL);
    return typeMetadata1->size == typeMetadata2->size && typeMetadata1->IsEqual == typeMetadata2->IsEqual;
}

int equalStrMeta(stringMetadata *stringMetadata1, stringMetadata *stringMetadata2) {
    assert(stringMetadata1 != NULL && stringMetadata2 != NULL);
    if (stringMetadata1 != stringMetadata2)
        return 0;
    if (!equalTypeMeta(stringMetadata1->typeMeta, stringMetadata2->typeMeta))
        return 0;
    return stringMetadata1->Recode == stringMetadata2->Recode &&
           stringMetadata1->Substring == stringMetadata2->Substring &&
           stringMetadata1->StrStr == stringMetadata2->StrStr && stringMetadata1->Concat == stringMetadata2->Concat &&
           stringMetadata1->CreateString == stringMetadata2->CreateString &&
           stringMetadata1->GetI == stringMetadata2->GetI && stringMetadata1->Delete == stringMetadata2->Delete;
}


voidString *Concat(voidString *voidStr1, voidString *voidStr2) {
    assert(voidStr1 != NULL && voidStr2 != NULL);
    assert(equalStrMeta(voidStr1->stringMeta, voidStr2->stringMeta));
    assert(voidStr1->data != NULL && voidStr2->data != NULL);
    voidString *res = CreateString(voidStr1->stringMeta, voidStr1->len + voidStr2->len);
    memcpy(res->data, voidStr1->data, voidStr1->len * voidStr1->stringMeta->typeMeta->size);
    memcpy(GetI(res, voidStr1->len), voidStr2->data,
           voidStr2->len * voidStr2->stringMeta->typeMeta->size);
    return res;
}

voidString *Recode(void *(*func)(void *), voidString *voidStr) {
    assert(func != NULL && voidStr != NULL);
    assert(voidStr->data != NULL);
    voidString *res = CreateString(voidStr->stringMeta, voidStr->len);
    for (int i = 0; i < voidStr->len; ++i) {
        memcpy(GetI(res, i), func(GetI(voidStr, i)), voidStr->stringMeta->typeMeta->size);
    }
    return res;
}

int Contains(voidString *voidStr1, voidString *voidStr2, int start, int n) {
    assert(voidStr1 != NULL && voidStr2 != NULL);
    assert(voidStr1->data != NULL && voidStr2->data != NULL);
    assert(start >= 0 && n >= 0);
    if (voidStr2->len > (voidStr1->len - start) || voidStr2->len < n)
        return 0;

    for (int i = start; i < start + n; ++i)
        if (!voidStr1->stringMeta->typeMeta->IsEqual(GetI(voidStr1, i), GetI(voidStr1, i - start)))
            return 0;
    return 1;
}

void *StrStr(voidString *voidStr1, voidString *voidStr2, int lower) {
    assert(voidStr1 != NULL && voidStr2 != NULL);
    assert(equalStrMeta(voidStr1->stringMeta, voidStr2->stringMeta));
    assert(voidStr1->data != NULL && voidStr2->data != NULL);
    assert(lower == 0 || lower == 1);
    if (lower) {
        voidStr1 = voidStr1->stringMeta->Recode(voidStr1->stringMeta->typeMeta->Lower, voidStr1);
        voidStr2 = voidStr2->stringMeta->Recode(voidStr2->stringMeta->typeMeta->Lower, voidStr2);
    }
    int start = 0;
    while (start <= voidStr1->len) {
        if (Contains(voidStr1, voidStr2, start, voidStr1->len))
            return GetI(voidStr1, start);
        start++;
    }

    return NULL;
}
//PolyArr Substring(size_t start, size_t length, PolyArr this) {
//    PolyArr res = CreatePolyArr();
//    res.len = length;
//    res.data = realloc(res.data, length * sizeof(PolyEl));
//    for (int i = 0; i < length; ++i)
//        res.data[i] = this.data[i + start];
//    return res;
//}

voidString *Substring(int a, int b, voidString *voidStr) {
    voidString *res = CreateString(voidStr->stringMeta, b - a + 1);
    res->data = memcpy(res->data, (char *) (voidStr->data) + a * voidStr->stringMeta->typeMeta->size,
                       b * voidStr->stringMeta->typeMeta->size);
    return res;
}


void *Delete(voidString *voidStr) {
    assert(voidStr != NULL);
    free(voidStr->data);
    free(voidStr);
    return NULL;
}

void *GetI(voidString *voidStr, int i) {
    assert(i >= 0 && i < voidStr->len);
    assert(voidStr != NULL);
    return (char *) (voidStr->data) + i * (voidStr->stringMeta->typeMeta->size);
}
