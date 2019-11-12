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