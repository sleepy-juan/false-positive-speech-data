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
    if (!wav.isValid())
    {
        std::cout << "Unable to open " << argv[1] << std::endl;
        return -1;
    }

    std::cout << "==============================" << std::endl;
    std::cout << "Sound Length: " << wav.getLengthInSeconds() << " sec" << std::endl;
    std::cout << "Sample Size(bytes): " << wav.getSampleSize() << " bytes" << std::endl;
    std::cout << "Sample Size(bits): " << wav.getSampleSizeInBits() << " bits" << std::endl;
    std::cout << "Channel Size: " << wav.getChannelSize() << std::endl;
    std::cout << "Sample Rate: " << wav.getSampleRate() << std::endl;
    std::cout << "Size(bytes): " << wav.getSize() << " bytes" << std::endl;
    std::cout << "Stored Size(bytes): " << wav.getBytes().size() << " bytes" << std::endl;

    wav.make(argv[2]);
    wav.makeHeader(argv[1] + std::string(".header"));
    wav.makeBody(argv[1] + std::string(".body"));

    Wav wav2(argv[2]);
    if (!wav2.isValid())
    {
        std::cout << "Unable to open " << argv[1] << std::endl;
        return -1;
    }

    std::cout << "==============================" << std::endl;
    std::cout << "Sound Length: " << wav2.getLengthInSeconds() << " sec" << std::endl;
    std::cout << "Sample Size(bytes): " << wav2.getSampleSize() << " bytes" << std::endl;
    std::cout << "Sample Size(bits): " << wav2.getSampleSizeInBits() << " bits" << std::endl;
    std::cout << "Channel Size: " << wav2.getChannelSize() << std::endl;
    std::cout << "Sample Rate: " << wav2.getSampleRate() << std::endl;
    std::cout << "Size(bytes): " << wav2.getSize() << " bytes" << std::endl;
    std::cout << "Stored Size(bytes): " << wav2.getBytes().size() << " bytes" << std::endl;
    std::cout << "==============================" << std::endl;

    wav2.makeHeader(argv[2] + std::string(".header"));
    wav2.makeBody(argv[2] + std::string(".body"));

    return 0;
}