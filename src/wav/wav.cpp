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
    fin.read(this->riff, 4);
    fin.read((char *)&this->riff_size, 4);
    fin.read(this->riff_wave, 4);

    /* FMT */
    fin.read(this->fmt, 4);
    fin.read((char *)&this->fmt_size, 4);
    fin.read((char *)&this->audio_format, 2);
    fin.read((char *)&this->n_channels, 2);
    fin.read((char *)&this->sample_rate, 4);
    fin.read((char *)&this->avg_byte_rate, 4);
    fin.read((char *)&this->block_align, 2);
    fin.read((char *)&this->bits_per_sample, 2);

    /* DATA */
    fin.read(this->data, 4);
    fin.read((char *)&this->size, 4);

    /* Body */
    this->bytes.reserve(this->size);
    std::copy(std::istream_iterator<uint8_t>(fin),
              std::istream_iterator<uint8_t>(),
              std::back_inserter(this->bytes));

    fin.close();
}

bool Wav::isRiffValid()
{
    return strncmp("RIFF", this->riff, 4) == 0 && strncmp("WAVE", this->riff_wave, 4) == 0;
}

bool Wav::isFmtValid()
{
    return strncmp("fmt ", this->fmt, 4) == 0;
}

bool Wav::isDataValid()
{
    return strncmp("data", this->data, 4) == 0;
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
    return this->n_channels;
}

uint32_t Wav::getSampleRate()
{
    return this->sample_rate;
}

uint16_t Wav::getSampleSizeInBits()
{
    return this->bits_per_sample;
}

std::vector<uint8_t> &Wav::getBytes()
{
    return this->bytes;
}

uint32_t Wav::getSize()
{
    return this->size;
}

/* computed variables */
uint16_t Wav::getSampleSize()
{
    return this->bits_per_sample / 8;
}

unsigned Wav::getLengthInSeconds()
{
    unsigned bytes_per_seconds = this->sample_rate * this->bits_per_sample / 8 * this->n_channels;
    return this->size / bytes_per_seconds;
}

/* write wav */
void Wav::make(std::string filename)
{
    std::ofstream fout(filename, std::ios::out | std::ios::binary);
    fout.unsetf(std::ios::skipws);

    /* RIFF Bitstream Format Info */
    fout.write(this->riff, 4);
    fout.write((char *)&this->riff_size, 4);
    fout.write(this->riff_wave, 4);

    /* FMT */
    fout.write(this->fmt, 4);
    fout.write((char *)&this->fmt_size, 4);
    fout.write((char *)&this->audio_format, 2);
    fout.write((char *)&this->n_channels, 2);
    fout.write((char *)&this->sample_rate, 4);
    fout.write((char *)&this->avg_byte_rate, 4);
    fout.write((char *)&this->block_align, 2);
    fout.write((char *)&this->bits_per_sample, 2);

    /* DATA */
    fout.write(this->data, 4);
    fout.write((char *)&this->size, 4);

    /* Body */
    fout.write((char *)&this->bytes[0], this->size);

    fout.close();
}