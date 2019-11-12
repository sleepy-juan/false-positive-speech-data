/*
    wav.cpp
    .wav file handler written in C++

    Created by Juan Lee
*/

#include "wav.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

Wav::Wav(std::string filename)
{
    this->_filename = filename;

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

const std::vector<uint8_t> &Wav::get()
{
    return data;
}

void Wav::set(std::vector<uint8_t> data)
{
    this->data.assign(data.begin(), data.end());
}

void Wav::clear()
{
    for (int i = 0; i < this->data.size(); i++)
    {
        this->data[i] = 0;
    }
}

std::vector<uint8_t> Wav::range(int start, int end)
{
    std::vector<uint8_t>::const_iterator first = this->data.begin() + start;
    std::vector<uint8_t>::const_iterator last = this->data.begin() + end;

    return std::vector<uint8_t>(first, last);
}

void Wav::replace(int start, std::vector<uint8_t> v)
{
    if (start < 0)
        start += this->data.size();
    std::vector<uint8_t>::iterator first = this->data.begin() + start;
    std::copy(v.begin(), v.end(), first);
}

unsigned Wav::size()
{
    return *(unsigned *)(this->header + 40);
}

std::string Wav::filename()
{
    return this->_filename;
}

unsigned Wav::sampleRate()
{
    return *(unsigned *)(this->header + 24);
}