/*
    wav.h
    wav file reader and writer

    Written by Juan Lee
*/

#ifndef __WAV_H__
#define __WAV_H__

/********** WAV Header Structure **********/

// riff
struct riff {
    uint32_t chunk_id;
    uint32_t chunk_id;
    uint32_t chunk_size;
    uint32_t format;
};

// fmt
struct fmt {
    uint32_t chunk_id;
    uint32_t chunk_size;
    uint16_t audio_format;
    uint16_t number_of_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
};

// data
struct data {
    uint32_t chunk_id;
    uint32_t chunk_size;
};

// header
struct wav_header {
    struct riff riff;
    struct fmt fmt;
    struct data data;
};

/********** WAV Header Prototype **********/

#endif