
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

#include "../wav/wav.hpp"
#include "../wav/wav.cpp"

using namespace std;


float bitwiseAverageDifference(std::string org_filename,  std::string mod_filename); 
int editDistance(std::string org_filename,  std::string mod_filename);

//testbed for trying out new functions.
int main(int argc, char **argv)
{
    Wav wav("../../audio/original/weather.wav");
    std::vector<uint8_t> v = wav.get();
    if(wav.valid())
    {
        std::cout << "wav valid!" << std::endl; 
    }
    else{
        std::cout << "Unable to open" << std::endl;
        return -1;
    }
    int answer = editDistance("../../audio/original/weather.wav", "../../audio/original/weather2.wav");
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
float bitwiseAverageDifference(std::string org_filename,  std::string mod_filename)
{
    Wav wav(org_filename);
    std::vector<uint8_t> original = wav.get();

    Wav wav2(mod_filename);
    std::vector<uint8_t> modified = wav2.get();

    float numRows = original.size();

    float average = 0;
    for(int i=0; i<numRows; i++){
        average+= abs(original.at(i) - modified.at(i))/numRows;
    }
    return average;
}


/*
    finds the edit distance between the inputs.
    only works for very short files due to extremely high space complexity
    uses 'sample rate' to reduce space complexity
*/
int editDistance(std::string org_filename,  std::string mod_filename)
{
    Wav wav(org_filename);
    std::vector<uint8_t> original = wav.get();

    Wav wav2(mod_filename);
    std::vector<uint8_t> modified = wav2.get();
    int sampleRate=500;

    int numRows = original.size()/sampleRate;
    int numCols = modified.size()/sampleRate;
    std::cout << numRows << std::endl;
    int ED[numRows][numCols];
    std::cout << numRows << std::endl;
    for(int i=0; i<=numRows; i++){
        for(int j=0; j<=numCols; j++){
            if(i==0)ED[i][j]=j;
            else if(j==0) ED[i][j]=i;
            else if(original[(i-1)*sampleRate]==modified[(j-1)*sampleRate]){
                ED[i][j]=ED[i-1][j-1];
            }
            else{
                ED[i][j] = 1 + min(ED[i][j-1],  // Insert 
                                   ED[i-1][j],  // Remove 
                                   ED[i-1][j-1]); // Replace 
            }
        }
    }
    return ED[numRows][numCols];
}
