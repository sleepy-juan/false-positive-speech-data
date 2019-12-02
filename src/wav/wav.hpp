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
    Class Wav
    
    This class contains wav format data and methods for manipulation.
*/
class Wav
{
private:
    uint8_t header[44];        // header info
    std::vector<uint8_t> data; // data
    std::string _filename;     // filename

public:
    Wav(std::string filename); // constructor with open the file

    /* About File */
    bool valid(bool debug = false);  // check validity
    void save(std::string filename); // save to the file

    /* Set & Get */
    uint8_t &operator[](int index);      // getter & setter
    const std::vector<uint8_t> &get();   // get all
    void set(std::vector<uint8_t> data); // set all
    void clear();                        // clear all

    /* Information */
    unsigned size();
    std::string filename();
    short numberOfChannel();
    unsigned sampleRate();
    unsigned byteRate();
    short blockAlign();
    short bitPerSample();
};

#endif