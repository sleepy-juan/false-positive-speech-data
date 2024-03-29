
/*
    various_fitness.cpp
    various candidate pseudo-human fitness functions

    best will be chosen after comparing with real human behaviour plotted by MTurk
    and will be used as the guidance function for the genetic algorithm.

    Created by Hyunchang Oh
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <cmath>

#include "../wav/wav.hpp"

using namespace std;

float bitwiseAverageDifference(std::string org_filename, std::string mod_filename);
float bitwiseSquaredDifference(std::string org_filename, std::string mod_filename);
float bitwiseGradientDifference(std::string org_filename, std::string mod_filename);
float bitwiseAverageCalibrated(std::string org_filename, std::string mod_filename);
int editDistance(std::string org_filename, std::string mod_filename);

//testbed for trying out new functions.
int main(int argc, char **argv)
{
    // std::cout << "hello world" << std::endl;
    Wav wav("test_audio/original.wav");
    std::vector<uint8_t> v = wav.get();
    if (wav.valid())
    {
        std::cout << "wav valid!" << std::endl;
    }
    else
    {
        std::cout << "Unable to open" << std::endl;
        return -1;
    }
    int answer = bitwiseAverageCalibrated("./test_audio/original.wav", "./test_audio/modified.wav");
    std::cout << answer << std::endl;
}

int min(int x, int y, int z)
{
    return min(min(x, y), z);
}

/*                                                            
    Calculates the average of all bitwise differences.
    Assume two input files are of equal length.
*/
float bitwiseAverageDifference(std::string org_filename, std::string mod_filename)
{
    Wav wav(org_filename);
    std::vector<uint8_t> original = wav.get();

    Wav wav2(mod_filename);
    std::vector<uint8_t> modified = wav2.get();

    float numRows = original.size();

    float average = 0;
    for (int i = 0; i < numRows; i++)
    {
        average += abs(original.at(i) - modified.at(i)) / numRows;
    }
    return average;
}

float bitwiseSquaredDifference(std::string org_filename, std::string mod_filename)
{
    Wav wav(org_filename);
    std::vector<uint8_t> original = wav.get();

    Wav wav2(mod_filename);
    std::vector<uint8_t> modified = wav2.get();

    float numRows = original.size();

    float average = 0;
    for (int i = 0; i < numRows; i++)
    {
        average += abs(original.at(i) - modified.at(i))* abs(original.at(i) - modified.at(i)) / numRows;
    }
    return average;
}

float bitwiseGradientDifference(std::string org_filename, std::string mod_filename)
{
    Wav wav(org_filename);
    std::vector<uint8_t> original = wav.get();

    Wav wav2(mod_filename);
    std::vector<uint8_t> modified = wav2.get();

    float numRows = original.size();

    float average = 0;
    for (int i = 0; i < numRows-1; i++)
    {
        float orgGradient = original.at(i) - original.at(i+1);
        float modGradient = modified.at(i) - modified.at(i+1);
        average += abs(orgGradient-modGradient)/numRows;
    }
    return average;
}

float bitwiseAverageCalibrated(std::string org_filename, std::string mod_filename)
{
    Wav wav(org_filename);
    std::vector<uint8_t> original = wav.get();

    Wav wav2(mod_filename);
    std::vector<uint8_t> modified = wav2.get();

    float numRows = original.size();

    float orgAverage = 0;
    float modAverage =0;
    for (int i = 0; i < numRows; i++)
    {
        orgAverage += original.at(i) /numRows;
        modAverage += modified.at(i) /numRows;
    }
    float average=0;
    for (int i=0; i< numRows; i++)
    {
        average += abs(abs(original.at(i)-orgAverage)-abs(modified.at(i)-modAverage))  /numRows;
    }
    return average;
}

/*
    finds the edit distance between the inputs.
    only works for very short files due to extremely high space complexity
    uses 'sample rate' to reduce space complexity
*/
int editDistance(std::string org_filename, std::string mod_filename)
{
    Wav wav(org_filename);
    std::vector<uint8_t> original = wav.get();

    Wav wav2(mod_filename);
    std::vector<uint8_t> modified = wav2.get();
    int sampleRate = 1;

    int numRows = original.size() / sampleRate;
    int numCols = modified.size() / sampleRate;

    // allocate
    int **ED = new int *[numRows];
    for (int i = 0; i < numRows; i++)
    {
        ED[i] = new int[numCols];
    }

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (i == 0)
                ED[i][j] = j;
            else if (j == 0)
                ED[i][j] = i;
            else if (original[(i - 1) * sampleRate] == modified[(j - 1) * sampleRate])
            {
                ED[i][j] = ED[i - 1][j - 1];
            }
            else
            {
                ED[i][j] = 1 + min(ED[i][j - 1],      // Insert
                                   ED[i - 1][j],      // Remove
                                   ED[i - 1][j - 1]); // Replace
            }
        }
    }

    int result = ED[numRows - 1][numCols - 1];

    // free
    for (int i = 0; i < numRows; i++)
    {
        delete[] ED[i];
    }
    delete[] ED;
    std::cout << "Freed" << std::endl;
    return result;
}
