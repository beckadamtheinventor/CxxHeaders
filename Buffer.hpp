/* Simple Read/Write Buffer classes
 * Author: Adam "beckadamtheinventor" Beckingham
 * License: MIT
 */
#pragma once

template<class T>
class RWBuffer {
    protected:
    T* ptr;
    size_t len;
    size_t offset;
    public:
    inline RWBuffer<T>(size_t len, size_t offset=0) {
		if (len == 0) {
			this->ptr = nullptr;
		} else {
			this->ptr = new T[len];
		}
        this->len = len;
        this->offset = offset;
    }
    inline RWBuffer<T>(T* ptr, size_t len, size_t offset=0) {
        this->ptr = ptr;
        this->len = len;
        this->offset = offset;
    }
    inline bool eof() {
        return offset >= len || ptr == nullptr;
    }
    inline size_t length() {
        return ptr==nullptr ? 0 : len;
    }
    inline size_t available() {
        return len - offset;
    }
    inline bool readable() {
        return ptr != nullptr;
    }
    inline bool writeable() {
        return ptr != nullptr;
    }
    inline void rewind() {
        offset = 0;
    }
	inline size_t tell() {
		return this->offset;
	}
	inline void seek(size_t offset) {
		this->offset = offset;
	}
	inline void seek(size_t offset, int dir) {
		if (dir == 0) {
			this->offset = offset;
		} else if (dir == 2) {
			this->offset = len > offset ? 0 : len - offset;
		} else if (dir == 1) {
			this->offset += offset;
			if (this->offset >= len) {
				this->offset = len;
			}
		}
	}
    inline T read() {
        if (ptr != nullptr && offset + 1 < len) {
            return ptr[offset++];
        }
        return T();
    }
    inline bool read(T& v) {
        if (offset + 1 < len) {
            v = ptr[offset++];
            return true;
        }
        return false;
    }
    size_t read(T* v, size_t amount) {
        if (ptr == nullptr) {
			return 0;
		}
		if (offset + amount >= len) {
            amount = len - offset;
        }
        for (size_t i=0; i<amount; i++) {
            v[i] = ptr[offset++];
        }
        return amount;
    }
    inline bool write(T v) {
        if (ptr == nullptr) {
			return false;
		}
        if (offset + 1 < len) {
            ptr[offset++] = v;
            return true;
        }
        return false;
    }
    size_t write(T* v, size_t amount) {
        if (ptr == nullptr) {
			return 0;
		}
        if (offset + amount >= len) {
            amount = len - offset;
        }
        for (size_t i=0; i<amount; i++) {
            ptr[offset++] = v[i];
        }
        return amount;
    }
};

template<class T>
class RBuffer : public RWBuffer<T> {
    inline bool write(T v) {}
    inline size_t write(T* v, size_t amount) {}
    inline bool writeable() {
        return false;
    }
};

template<class T>
class WBuffer : public RWBuffer<T> {
    inline T read() {}
    inline bool read(T& v) {}
    inline size_t read(T* v, size_t amount) {}
    inline bool readable() {
        return false;
    }
};
