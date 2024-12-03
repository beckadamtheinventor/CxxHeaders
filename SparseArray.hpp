#pragma once

#include <vector>
template<class T, size_t CHUNK_SIZE=16>
class SparseArray {
    protected:
    std::vector<T[CHUNK_SIZE]> _buckets;
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
        return _buckets.size()*CHUNK_SIZE;
    }
};