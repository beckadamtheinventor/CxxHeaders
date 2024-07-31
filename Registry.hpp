/* Simple Registry class. (integer and string keyed dictionary)
 * Author: Adam "beckadamtheinventor" Beckingham
 * License: MIT
 */
#pragma once

#include <cstdio>
#include <exception>

#include "DynamicArray.hpp"
#include "Dictionary.hpp"

template<class T>
class Registry {
    protected:
    DynamicArray<T*> _entries;
    Dictionary<size_t> _dict;
    size_t nextid() {
        return _entries.length();
    }
    public:
    /* Clear the registry.
     * Note that all values must be allocated with the "new" operator otherwise this will not work expectedly.
     */
    void clear() {
        _dict.clear();
        for (size_t i=0; i<_entries.length(); i++) {
            delete _entries[i];
        }
    }
    /* Get the number of registered entries. */
    size_t length() {
        return _entries.length();
    }
    /* Add a new key:value pair to the registry, returning a pointer to it.
     * Note that the value should be allocated with the "new" operator.
     */
    T* add(const char *key, T* v) {
        size_t id = nextid();
        _entries.append(v);
        _dict.append(key, id);
        return v;
    }
    /* Create a new key:empty pair in the registry, returning a pointer to it. */
    T* create(const char *key) {
        return add(key, new T());
    }
    /* Check if the registry contains a given key. */
	bool has(const char *key) {
		return _dict.has(key);
	}
    /* Get a registry entry from a given key. */
	T& get(const char *key) {
		if (has(key)) {
			return _entries[_dict[key]];
		}
        printf("Registry key \"%s\" undefined.\n", key);
		throw std::exception();
	}
    /* Check if the registry contains an entry of a given integer id. */
	bool has(size_t id) {
		return id < _entries.length();
	}
    /* Get a registry entry given an integer id. */
	T* get(size_t id) {
		if (has(id)) {
			return _entries[id];
		}
        printf("Registry ID %llu out of range.\n", id);
		throw std::exception();
	}
    /* Get a registry key given an integer id. */
    const char* keys(size_t id) {
        if (has(id)) {
            return _dict.keys(id);
        }
        printf("Registry ID %llu out of range.\n", id);
        throw std::exception();
    }
};
