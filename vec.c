#include "vec.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * vecCreate: creates and initializes new vector
 * elemSize - size of elements to be stored
 */
vec* vecCreate(size_t elemSize){
    vec* v = (vec*) malloc(sizeof(vec));
    v->capacity = 1;
    v->size = 0;
    v->vector = malloc(elemSize);
    v->elemSize = elemSize;
    return v;
}

/**
 * vecFree: frees all memory used by v
 * dont need to free v later
 * v - vector to be freed
 */
void vecFree(vec* v){
    free(v->vector);
    free(v);
}

/**
 * adjustCapacity: moves all elements from v->vector to a new
 * array of size newCapacity
 * v - pointer to vec
 * newCapacity - ...
 */
void adjustCapacity(vec *const v, size_t newCapacity){
    // update capacity
    v->capacity = newCapacity;
    unsigned char* newVec = malloc(v->capacity * v->elemSize);
    unsigned char* data = (unsigned char*) v->vector;

    // copy each byte to new array
    for(int i = 0; i < v->elemSize * v->size; i++){
        newVec[i] = data[i];
    }

    // free uneeded mem
    v->vector = (void*) newVec;
    free(data);
}

/**
 * vecPush: pops last elem of v and shrinks if necessary
 * v - pointer to vector
 */
void vecPop(vec *const v){
    v->size--;

    // adjust if needed
    if (v->size * 2 == v->capacity){
        adjustCapacity(v, v->capacity/2);
    }

}

/**
 * vecPush: pushes e to the end of v and expands if necessary
 * v - pointer to vector
 * e - pointer to element to push
 */
void vecPush(vec *const v, const void *const e){
    // if current vector is full
    if(v->size == v->capacity){
        adjustCapacity(v, v->capacity*2);
    }
    unsigned char* newVec = (unsigned char*) v->vector;
    unsigned char* elem = (unsigned char*) e;

    // copy to new array starting at start index
    int startIndex = v->elemSize * v->size;
    for (int i = 0; i < v->elemSize; i++){
        newVec[startIndex + i] = elem[i];
    }

    v->vector = (void*) newVec;
    v->size++;
}

/**
 * vecAt: returns elem at idx
 * v - vector
 * idx - index to return
 * returns pointer to heap, free it
 */
void* vecAt(const vec *const v, size_t idx){
    unsigned char* elem = malloc(v->elemSize);
    unsigned char* vector = (unsigned char*) v->vector;

    size_t startIndex = idx * v->elemSize;
    for(int i = 0; i < v->elemSize; i++){
        elem[i] = vector[startIndex + i];
    }
    return elem;
}
/**
 * vecInsert: insert e at idx
 * v - vector
 * e - element to be inserted
 * idx - index
 * returns false if idx is greater than size
 */
bool vecInsert(vec *const v, const void *const e, size_t idx){
    if(idx > v->size){
        return false;
    }

    if(v->size == v->capacity){
        adjustCapacity(v, v->capacity*2);
    }
    unsigned char* vector = (unsigned char*) v->vector;
    unsigned char* elem = (unsigned char*) e;

    for(int i = v->size * v->elemSize - 1; i != idx * v->elemSize - 1; i--){
        vector[i + v->elemSize] = vector[i];
    }

    for(int i = 0; i < v->elemSize; i++){
        vector[idx * v->elemSize + i] = elem[i];
    }

    v->vector = (void*) vector;
    v->size++;
    return true;
}

/**
 * vecRemove: remove element at idx
 * v - vector
 * idx - index
 * returns false if idx is greater than size
 */
bool vecRemove(vec *const v, size_t idx){
    if(idx > v->size){
        return false;
    }

    if(v->size*2 == v->capacity){
        adjustCapacity(v, v->capacity/2);
    }
    unsigned char* vector = (unsigned char*) v->vector;

    for(int i = (idx + 1) * v->elemSize; i < v->size * v->elemSize - 1; i++){
        vector[i - v->elemSize] = vector[i];
    }

    v->vector = (void*) vector;
    v->size--;
    return true;
}

/**
 * vecFind: finds first idx where e appears
 * literally just compares bytes stored, doesnt do anything fancy
 * good luck using on float vec
 * v - vec
 * e - elem to find
 * returns idx
 */
size_t vecFind(const vec *const v, const void *const e){
    unsigned char* vector = (unsigned char*) v->vector;
    unsigned char* elem = (unsigned char*) e;

    size_t count;
    for(int i = 0; i < v->size; i++){
        count = 0;
        for(int j = 0; j < v->elemSize; j++){
            if(vector[i*v->elemSize + j] != elem[j]){
                break;
            }
            count++;
        }
        if(count == v->elemSize){
            return i;
        }
    }

}


size_t vecCapacity(const vec *const v){
    return v->capacity;
}

size_t vecElemSize(const vec *const v){
    return v->elemSize;
}

size_t vecSize(const vec *const v){
    return v->size;
}