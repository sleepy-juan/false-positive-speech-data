/*
    wav.hpp
    .wav file handler written in C++

    Created by Juan Lee
*/

#ifndef __WAV_HPP__
#define __WAV_HPP__

#include <vector>
#include <string>

/*
    Wav Class
    - contains wav format file information as attributes
    - maintains handling methods for wav format file
*/
class Wav
{
private:
    //--------- HEADER ----------
    /* RIFF Bitstream Format Info */
    char riff[4];       // "riff"
    uint32_t riff_size; // overall size of file in bytes
    char riff_wave[4];  // "wave"

    /* FMT */
    char fmt[4];              // "fmt "
    uint32_t fmt_size;        // length of fmt
    uint16_t audio_format;    // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    uint16_t n_channels;      // # of channels
    uint32_t sample_rate;     // sample rate (blocks per second)
    uint32_t avg_byte_rate;   // sample rate * # of channels * bytes per sample
    uint16_t block_align;     // # of channels * bytes per sample
    uint16_t bits_per_sample; // bits per sample, 8- 8bits, 16- 16 bits etc

    /* DATA */
    char data[4];  // "data"
    uint32_t size; // data size

    //--------- Info ----------
    std::string filename;
    std::vector<uint8_t> bytes;

    //--------- Private Methods ----------
    void load();

    bool isRiffValid();
    bool isFmtValid();
    bool isDataValid();

public:
    /* constructor & destructor */
    Wav(std::string filename);

    /* format validity */
    bool isValid();

    /* getters */
    uint16_t getChannelSize();
    uint32_t getSampleRate();
    uint16_t getSampleSizeInBits();
    std::vector<uint8_t> &getBytes();
    uint32_t getSize();

    /* computed variables */
    uint16_t getSampleSize();
    unsigned getLengthInSeconds();

    /* write wav */
    void make(std::string filename);
};

#endif