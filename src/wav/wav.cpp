/*
    wav.cpp
    .wav file handler written in C++

    Created by Juan Lee
*/

#include "wav.hpp"

#include <fstream>
#include <iostream>

//--------- Private Methods ----------
void Wav::load()
{
    std::ifstream fin(this->filename, std::ios::binary);
    fin.unsetf(std::ios::skipws);

    /* RIFF Bitstream Format Info */
    fin.read(this->header.riff, 4);
    fin.read((char *)&this->header.riff_size, 4);
    fin.read(this->header.riff_wave, 4);

    /* FMT */
    fin.read(this->header.fmt, 4);
    fin.read((char *)&this->header.fmt_size, 4);
    fin.read((char *)&this->header.audio_format, 2);
    fin.read((char *)&this->header.n_channels, 2);
    fin.read((char *)&this->header.sample_rate, 4);
    fin.read((char *)&this->header.avg_byte_rate, 4);
    fin.read((char *)&this->header.block_align, 2);
    fin.read((char *)&this->header.bits_per_sample, 2);

    /* DATA */
    fin.read(this->header.data, 4);
    fin.read((char *)&this->header.size, 4);

    /* Body */
    this->bytes.reserve(this->header.size);
    std::copy(std::istream_iterator<uint8_t>(fin),
              std::istream_iterator<uint8_t>(),
              std::back_inserter(this->bytes));

    fin.close();
}

bool Wav::isRiffValid()
{
    return strncmp("RIFF", this->header.riff, 4) == 0 && strncmp("WAVE", this->header.riff_wave, 4) == 0;
}

bool Wav::isFmtValid()
{
    return strncmp("fmt ", this->header.fmt, 4) == 0;
}

bool Wav::isDataValid()
{
    return strncmp("data", this->header.data, 4) == 0;
}

//--------- Public Methods ----------

/* constructor & destructor */
Wav::Wav(std::string filename)
    : filename(filename)
{
    this->load(); // load wav file data
}

/* format validity */
bool Wav::isValid()
{
    return this->isRiffValid() && this->isFmtValid() && this->isDataValid();
}

/* getters */
uint16_t Wav::getChannelSize()
{
    return this->header.n_channels;
}

uint32_t Wav::getSampleRate()
{
    return this->header.sample_rate;
}

uint16_t Wav::getSampleSizeInBits()
{
    return this->header.bits_per_sample;
}

std::vector<uint8_t> &Wav::getBytes()
{
    return this->bytes;
}

uint32_t Wav::getSize()
{
    return this->header.size;
}

/* computed variables */
uint16_t Wav::getSampleSize()
{
    return this->header.bits_per_sample / 8;
}

unsigned Wav::getLengthInSeconds()
{
    unsigned bytes_per_seconds = this->header.sample_rate * this->header.bits_per_sample / 8 * this->header.n_channels;
    return this->header.size / bytes_per_seconds;
}

/* write wav */
void Wav::make(std::string filename)
{
    std::ofstream fout(filename, std::ios::out | std::ios::binary);
    fout.unsetf(std::ios::skipws);

    /* RIFF Bitstream Format Info */
    fout.write(this->header.riff, 4);
    fout.write((char *)&this->header.riff_size, 4);
    fout.write(this->header.riff_wave, 4);

    /* FMT */
    fout.write(this->header.fmt, 4);
    fout.write((char *)&this->header.fmt_size, 4);
    fout.write((char *)&this->header.audio_format, 2);
    fout.write((char *)&this->header.n_channels, 2);
    fout.write((char *)&this->header.sample_rate, 4);
    fout.write((char *)&this->header.avg_byte_rate, 4);
    fout.write((char *)&this->header.block_align, 2);
    fout.write((char *)&this->header.bits_per_sample, 2);

    /* DATA */
    fout.write(this->header.data, 4);
    fout.write((char *)&this->header.size, 4);

    /* Body */
    fout.write((char *)&this->bytes[0], this->header.size);

    fout.close();
}