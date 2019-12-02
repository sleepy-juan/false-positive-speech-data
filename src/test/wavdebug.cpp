/*
    wav.cpp

    Created by Juan Lee
*/

#include <iostream>
#include <vector>

#include "../wav/wav.hpp"

int main(int argc, char **argv)
{
    for (int i = 1; i < 8; i++)
    {
        Wav wav("../../audio/original/" + std::to_string(i) + ".wav");
        std::cout << wav.valid(true) << std::endl;
    }

    Wav wav("../../audio/original/test2.wav");
    std::cout << wav.valid(true) << std::endl;
    return 0;
}