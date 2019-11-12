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
    uint8_t &operator[](int index); // getter & setter

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

## Example

```cpp
/*
    wav.cpp

    Created by Juan Lee
*/

#include <iostream>

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

    wav.save(argv[2]);
    return 0;
}
```

