# Wav Document

This document explains the usage of `Wav` defined in `src/wav/wav.hpp`.

## Overview

```cpp
// src/wav/wav.hpp

class Wav
{
private:
    ...

public:
    Wav(std::string filename); // constructor with open the file

    /* About File */
    bool valid();                    // check validity
    void save(std::string filename); // save to the file

    /* Set & Get */
    uint8_t &operator[](int index);                  // getter & setter
    const std::vector<uint8_t> &get();               // get all
    void set(std::vector<uint8_t> data);             // set all
    void clear();                                    // clear all
    std::vector<uint8_t> range(int start, int end);  // range [start, end) - end is not ...
    void replace(int start, std::vector<uint8_t> v); // replace the data with given ...

    /* Information */
    unsigned size();
};
```

## Methods

### Constructor

Hopely, there is only one constructor.

```cpp
Wav(std::string filename);
```

It gets `filename` as a parameter, and loads the data from the file.

### valid

`valid` method returns a boolean value indicating the validity of the wav file.

```cpp
bool valid();
```

### save

`save` method gets `filename` as a parameter and stores the data to the file.

```cpp
void save(std::string filename);
```

### size

`size` method returns the size of data excluding the size of header.

```cpp
unsigned size();
```

### Indexer

You can use indexing just like other data structures.

```cpp
uint8_t &operator[](int index);
```

It also may take negative values in range of `-size` $\le$ `index` $\le$ `-1` . 

### get

`get` returns the vector of bytes.

```cpp
const std::vector<uint8_t> &get();
```

### set

`set` replaces the data with the given vector.

```cpp
void set(std::vector<uint8_t> data);
```

### clear

`clear` sets all the bytes as `0`.

```cpp
void clear();
```

### range

`range` returns a sub-vector of data.

```cpp
std::vector<uint8_t> range(int start, int end);
```

Note that it does not include the `end` byte of the data.

### replace

`replace` replaces a subvector of data with given vector.

```cpp
void Wav::replace(int start, std::vector<uint8_t> v);
```

Make sure your length of vector is valid. If not, it will make an undefined behavior.

## Example

```cpp
/*
    wav.cpp

    Created by Juan Lee
*/

#include <iostream>
#include <vector>

#include "../wav/wav.hpp"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << "from.wav to.wav" << std::endl;
        return -1;
    }

    Wav wav(argv[1]);
    if (!wav.valid())
    {
        std::cout << "Unable to open " << argv[1] << std::endl;
        return -1;
    }

    // print bytes
    std::cout << (int)wav[1000] << std::endl; // 1000-th
    std::cout << (int)wav[-1] << std::endl;   // last

    // set bytes
    wav[-1] = wav[-2] = wav[-3] = wav[-4] = wav[-5] = 0;

    // swap
    std::swap(wav[-1], wav[-6]); // use standard swap, also valid for two different wavs

    // get all
    std::vector<uint8_t> v = wav.get();

    // get range
    std::vector<uint8_t> r = wav.range(20000, 20050);
    for (auto elem : r)
    {
        std::cout << (int)elem << " ";
    }
    std::cout << std::endl;

    // clear
    wav.clear();

    // check clearance
    r = wav.range(20000, 20050);
    for (auto elem : r)
    {
        std::cout << (int)elem << " ";
    }
    std::cout << std::endl;

    // set & replace
    wav.set(v);
    wav.replace(-100, r);

    // save
    wav.save(argv[2]);
    return 0;
}
```

