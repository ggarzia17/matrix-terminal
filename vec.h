#ifndef VEC_H
#define VEC_H

#include <stdbool.h>
#include <stdlib.h>

// dont fuck with member vars pls
typedef struct {
    size_t elemSize;
    size_t size;
    size_t capacity;
    void* vector;
} vec;

void vecPop(vec *const v);
void vecPush(vec *const v, const void *const e);
void* vecAt(const vec *const v, size_t idx);
bool vecInsert(vec *const v, const void *const e, size_t idx);
bool vecRemove(vec *const v, size_t idx);
size_t vecFind(const vec *const v, const void *const e);
vec* vecCreate(size_t elemSize);
void vecFree(vec* v);
size_t vecCapacity(const vec *const v);
size_t vecElemSize(const vec *const v);
size_t vecSize(const vec *const v);

#endif