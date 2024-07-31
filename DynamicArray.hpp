/* Simple Dynamic Array class.
 * Author: Adam "beckadamtheinventor" Beckingham
 * License: MIT
 */
#pragma once

#include <cstddef>

template<class T, size_t MIN_ALLOC=256>
class DynamicArray {
    size_t len;
    size_t alloc;
    T *items;
    public:
	/* Construct an empty Dynamic Array (MIN_ALLOC items allocated) */
    DynamicArray<T, MIN_ALLOC>() {
        len = 0;
        alloc = MIN_ALLOC;
        items = new T[alloc];
    }
	/* Construct a Dynamic Array with size elements allocated. */
    DynamicArray<T, MIN_ALLOC>(size_t size) {
        len = 0;
        alloc = size;
        items = new T[alloc];
    }
	/* Construct a Dynamic Array from existing elements. */
    DynamicArray<T, MIN_ALLOC>(T* elements, size_t size) {
        len = alloc = size;
        items = new T[alloc];
        for (size_t i=0; i<alloc; i++) {
            items[i] = elements[i];
        }
    }
	/* Construct (deep copy) a Dynamic Array from another Dynamic Array. */
	DynamicArray<T, MIN_ALLOC>(DynamicArray& other) {
		alloc = len = other.length();
		items = new T[alloc];
		for (size_t i=0; i<alloc; i++) {
			items[i] = other[i];
		}
	}
	/* Clear the Array. Note: uses default constructor for T. */
    void clear() {
        for (size_t i=0; i<len; i++) {
            items[i] = T();
        }
        len = 0;
    }
	/* Return the number of items in the Array. */
    size_t length() {
        return len;
    }
	/* Return the number of allocated items in the Array. */
    size_t available() {
        return alloc - len;
    }
	/* Resize the Array to allocate more or less items. Note: can be zero. */
    void resize(size_t size) {
        if (size > 0) {
            T *newitems = new T[size];
            if (items != nullptr) {
                for (size_t i=0; i<size; i++) {
                    if (i < len) {
                        newitems[i] = items[i];
                    }
                }
                delete items;
            }
            items = newitems;
            alloc = size;
        } else {
            delete items;
            items = nullptr;
            alloc = len = 0;
        }
    }
	/* Get/Set an item in the Array. Note: can be outside the bounds of the array to add items. Use with care.
	   Resizes the array to contain i+MIN_ALLOC items if adding. */
    T& get(size_t i) {
        if (i >= alloc) {
            resize(i + MIN_ALLOC);
        }
        if (i >= len) {
            len = i + 1;
		}
        return items[i];
    }
	/* Get/Set an item in the Array. Note: can be outside the bounds of the array to add items. Use with care.
	   Resizes the array to contain i+MIN_ALLOC items if adding. */
    inline T& operator[](size_t i) {
        return get(i);
    }
	/* Set an item in the array at a specified index. */
    T& add(size_t i, T value) {
        return (get(i) = value);
    }
	/* Add an item to the end of the Array. */
    T& append(T value) {
        return add(len, value);
    }
	/* Remove the item at index i. Note: copies all successive items back. Can be very slow. */
    void remove(size_t i) {
        if (len == 0) {
            return;
        }
        delete items[i];
        for (size_t j=i; j<len-1; j++) {
            items[j] = items[j+1];
        }
        items[len-1] = T();
    }
	/* De-allocate unset allocated entries in the Array. */
    void trim() {
        resize(len);
    }
	/* Return a pointer to a trimmed copy of the Array's contents. */
    T* collapse() {
        if (len == 0) {
            return nullptr;
        }
        T* newitems = new T[len];
        for (size_t i=0; i<len; i++) {
            newitems[i] = items[i];
        }
        return newitems;
    }
	/* Return a pointer to the Array's contents. */
    operator T*() {
        return items;
    }
};
