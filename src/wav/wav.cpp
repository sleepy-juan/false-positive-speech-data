/*
    wav.cpp
    .wav file handler written in C++

    Created by Juan Lee
*/

#include "wav.hpp"

#include <fstream>
#include <iostream>

Wav::Wav(std::string filename)
{
    std::ifstream fin(filename, std::ios::binary);
    fin.unsetf(std::ios::skipws);
    fin.read((char *)this->header, 44);

    this->data.reserve(*(int *)(this->header + 40));
    std::copy(std::istream_iterator<uint8_t>(fin),
              std::istream_iterator<uint8_t>(),
              std::back_inserter(this->data));

    fin.close();
}

bool Wav::valid()
{
    return strncmp("RIFF", (char *)this->header, 4) == 0 &&
           strncmp("WAVE", (char *)(this->header + 8), 4) == 0 &&
           strncmp("fmt ", (char *)(this->header + 12), 4) == 0 &&
           strncmp("data", (char *)(this->header + 36), 4) == 0;
}

void Wav::save(std::string filename)
{
    std::ofstream fout(filename, std::ios::out | std::ios::binary);
    fout.unsetf(std::ios::skipws);
    fout.write((char *)this->header, 44);
    fout.write((char *)&this->data[0], *(int *)(this->header + 40));
    fout.close();
}

uint8_t &Wav::operator[](int index)
{
    if (index < 0) // only allow python-styled list indexing
        index += this->data.size();
    return data[index];
}

unsigned Wav::size()
{
    return *(int *)(this->header + 40);
}