# Beck's Cxx Headers

Just a collection of C++ headers containing implementations for common things so I don't have to keep rewriting them.

Author: Adam "beckadamtheinventor" Beckingham.

License: MIT.


## Data Classes

+ Array2D
+ Dictionary
+ DynamicArray
+ SimpleConfig::Config


## Static Classes

+ AssetPath



## Array2D.hpp

Simple 2D array class.

Constructors:
+ `Array2D<class T>();` Construct an empty 2D Array.
+ `Array2D<class T>(size_t width, size_t height);` Construct a 2D Array of width x height.
+ `Array2D<class T>(size_t width, size_t height, T* values);` Construct a 2D Array of width x height from existing values.

Member Functions:
+ `size_t width();` Returns width of the 2D array.
+ `size_t height();` Returns height of the 2D array.
+ `size_t size();` Returns size (width x height) of the 2D array.
+ `void resize(size_t width, size_t height)` Resize the 2D array. Destroys all data.
+ `T& operator[](ArrayIndex i)` Get/Set a value in the 2D array. Note: ArrayIndex can be easily constructed with brackets. (`{x, y}`)
+ `operator T*()` Get a pointer to the Array's values in a flat array.


## AssetPath.hpp

Class containing static functions for constructing temporary paths for asset loading.

Note: all of these functions return a pointer to a temporary buffer that is overwritten the next time an AssetPath function is called.
The concat function does not use this buffer nor write this buffer.

Static Functions:
+ `char* concat(char *p, const char* path, const char* name, const char* type)` Returns a path to "<path>/<name>.<type>". Writes the data to p.
+ `char* root(const char* name, const char* type)` Returns a path to "assets/<name>.<type>".
+ `char* level(const char* name, const char* type)` Returns a path to "assets/levels/<name>.<type>".
+ `char* map(const char* name, const char* type)` Returns a path to "assets/maps/<name>.<type>".
+ `char* object(const char* name, const char* type)` Returns a path to "assets/objects/<name>.<type>".
+ `char* texture(const char* name, const char* type)` Returns a path to "assets/textures/<name>.<type>".



## Buffer.hpp

Simple read/write buffer classes.

### RWBuffer, RBuffer, WBuffer

Constructors:
+ `RWBuffer<T>(size_t len, size_t offset=0)` Initialize a buffer for reading and writing, optionally with offset.
+ `RWBuffer<T>(T* ptr, size_t len, size_t offset=0)` Initialize a buffer for reading and writing, optionally with offset.

Member Fucntions:
+ `bool eof()` Returns true if the buffer has no more data left to read/write or if the data pointer is null.
+ `size_t length()` Returns the size of the buffer.
+ `size_t available()` Returns the remaining elements in the buffer.
+ `bool readable()` Returns true for RWBuffer and RBuffer classes.
+ `bool writeable()` Returns true for RWBuffer and WBuffer classes.
+ `void rewind()` Rewind the data buffer.
+ `size_t tell()` Return the current offset in the buffer.
+ `void seek(size_t offset)` Seek to an offset in the buffer. (abolute)
+ `void seek(size_t offset, int dir)` Seek to an offset in the buffer. dir must be SEEK_START, SEEK_CUR, or SEEK_END.
+ `T read()` Read one element from the buffer. Use this only if you know there are elements to read; it will error silently otherwise.
+ `bool read(T& v)` Read one element from the buffer, returning true if successful.
+ `size_t read(T* v, size_t amount)` Read amount elements from the buffer, returning the number of elements read.
+ `bool write(T& v)` Write one element to the buffer, returning true if successful.
+ `size_t write(T* v, size_t amount)` Write amount elements to the buffer, returning the number of elements written.



## Dictionary.hpp

Simple string keyed dictionary class. Saves keys for later use, ideal for serialization/deserialization.

Relies on DynamicArray.hpp.

Note that the index of a given key:value pair will likely not persist when the Dictionary is modified.

Constructors:
+ `Dictionary<T, MIN_ALLOC=64, BUCKETS=64>()` Construct an empty Dictionary.
+ `Dictionary<T, MIN_ALLOC=64, BUCKETS=64>(const char* *keys, const T* values, size_t count)` Construct a Dictionary from existing keys and values.

Member Functions:
+ `void clear()` Clear the Dictionary, removing all keys and values.
+ `size_t length()` Returns the number of key:value pairs.
+ `bool has(const char* key)` Returns true if the key is found in the Dictionary.
+ `bool has(size_t i)` Return true if index i is less than the number of key:value pairs.
+ `T& get(const char* key)` Get/Set a key:value pair in the Dictionary. key:value pair (default constructor for T value) is created if it doesn't exist.
+ `T& get(size_t i)` Get/Set key:value pair index in the Dictionary.
+ `T& add(const char* key, const T value)` Set a key/value pair in the Dictionary.
+ `T& append(const char* key, const T value)` Same as add.
+ `T& operator[](const char* key)` Same as get.
+ `T values(size_t i)` Returns value at index i.
+ `char* keys(size_t i)` Returns key at index i.


## SimpleConfig.hpp

Simple binary serialized non-recursive configuration library.

Relies on Dictionary.hpp

### SimpleConfig::Config

Constructors:
+ `SimpleConfig::Config()`

Member Functions:
+ `bool isBool(const char* key)`
+ `bool isInteger(const char* key)`
+ `bool isUnsigned(const char* key)`
+ `bool isFloat(const char* key)`
+ `bool isNumber(const char* key)`
+ `bool isString(const char* key)`
+ `bool getBool(const char* key)`
+ `long long getInteger(const char* key)`
+ `size_t getUnsigned(const char* key)`
+ `double getFloat(const char* key)`
+ `char* getString(const char* key)`
+ `void set(const char* key, Value v)`
+ `void setBool(const char* key, bool v)`
+ `void setInteger(const char* key, long long v)`
+ `void setUnsigned(const char* key, size_t v)`
+ `void setFloat(const char* key, double v)`
+ `void setString(const char* key, const char* v)`
+ `size_t length()`
+ `void add(const char* key, Value val)` Same as set.
+ `bool deserialize(const char *fname)` Deserialize binary or text formatted data from file fname. Returns false if failed or the header is incorrect.
+ `bool deserialize(std::istream* in)` Deserialize binary formatted data from istream. Does not check for a header.
+ `bool deserializeText(std::istream* in)` Deserialize text formatted config data from istream. Does not check for a header.
+ `bool serialize(const char *fname)` Serialize config data as a binary formatted file fname. Writes a header.
+ `bool serialize(std::ostream* out)` Serialize config data as binary to ostream. Does not write a header.

Notes:
+ There is currently no serialization to text
+ Loading from text may or may not work

### SimpleConfig::Value

Constructors:
+ `Value()`

Static Functions:
+ `Value Value::deserialize(char *buf, size_t l)` Deserialize value from binary data.
+ `Value Value::deserializeText(std::istream* in, bool& success)` Deserialize value from text data. success=true if success, false if failed.
+ `Value Value::fromBool(bool b)`
+ `Value Value::fromInteger(long long i)`
+ `Value Value::fromUnsigned(size_t u)`
+ `Value Value::fromDouble(double f)`
+ `Value Value::fromString(std::string s)`
+ `Value Value::fromString(const char* s)`

Member Functions:
+ `size_t serialize(char* buf)` Serialize value to buffer in binary format. Returns bytes written.
+ `bool isBool()` Returns true if the value is true or false.
+ `bool isInteger()` Returns true if the value is an integer.
+ `bool isUnsigned()` Returns true if the value is an unsigned integer.
+ `bool isUnsigned()` Returns true if the value is an unsigned integer.
+ `bool isFloat()` Returns true if the value is a floating point number.
+ `bool isNumber()` Returns true if the value is an integer, unsigned integer, or floating point number.
+ `bool isString()` Returns true if the value is a string.
+ `bool getBool()` Returns false if the value is a false boolean, else true.
+ `long long getInteger()` Returns the value as an integer if possible, otherwise 0.
+ `size_t getUnsigned()` Returns the value as an unsigned integer if possible, otherwise 0.
+ `float getDouble()` Returns the value as a single-precision floating point number if possible, otherwise NAN.
+ `double getDouble()` Returns the value as a double-precision floating point number if possible, otherwise NAN.
+ `char* getString()` Returns the value if it is a string, otherwise nullptr.


