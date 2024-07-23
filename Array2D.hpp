/* Simple Array2D class.
 * Author: Adam "beckadamtheinventor" Beckingham
 * License: MIT
 */
#pragma once

#include <cstddef>
#include <cstdio>
#include <exception>
#include <stdio.h>

struct ArrayIndex {
    size_t x, y;
};

template<class T>
class Array2D {
    size_t w, h, l;
    T** values;
    public:
    /* Construct an empty 2D array. */
    Array2D<T>() : Array2D<T>(0, 0) {}
    /* Construct a 2D array of size width * height */
    Array2D<T>(size_t width, size_t height) {
		values = nullptr;
		resize(width, height);
    }
    /* Construct a 2D array of size width * height from existing values */
    Array2D<T>(size_t width, size_t height, T* values) : Array2D<T>(width, height) {
        size_t i = 0;
        for (size_t y = 0; y < height; y++) {
            T* row = values[y];
            for (size_t x = 0; x < width; x++) {
                row[x] = values[i++];
            }
        }
    }
    /* Resize a 2D Array. Note: Destroys the data. */
	void resize(size_t width, size_t height) {
		if (values != nullptr) {
			delete values;
		}
        w = width;
        h = height;
        l = w * h;
        if (l > 0) {
            values = new T*[height];
            for (size_t i = 0; i < height; i++) {
                values[i] = new T[width];
            }
        } else {
            values = nullptr;
        }
	}
	
    /* Returns the width of the 2D Array. */
    size_t width() {
        return w;
    }
    /* Returns the height of the 2D Array. */
    size_t height() {
        return h;
    }
    /* Returns the size (width*height) of the 2D Array. */
    size_t size() {
        return l;
    }   
    /* Get/Set an item in the array.
       Note: ArrayIndex can be easily constructed with brackets. ({x, y}) */
    T& operator[](ArrayIndex i) {
        if (i.x < w && i.y < h) {
            return values[i.y][i.x];
        }
        printf("Array2D Index out of range\n");
        throw std::exception();
    }
};
