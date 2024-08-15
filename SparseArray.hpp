#pragma once

#include "DynamicArray.hpp"

template<class T, size_t CHUNK_SIZE=16, size_t MIN_ALLOC=16>
class SparseArray {
    protected:
    DynamicArray<T[CHUNK_SIZE], MIN_ALLOC> _buckets;
    public:
    SparseArray<T>() {}
    SparseArray<T>(T* values, unsigned int count) {
        for (unsigned int i=0; i<count; i++) {
            get(i) = values[i];
        }
    }
    T& get(unsigned int i) {
        return _buckets[i / CHUNK_SIZE][i % CHUNK_SIZE];
    }
    unsigned int length() {
        return _buckets.length()*CHUNK_SIZE;
    }
};