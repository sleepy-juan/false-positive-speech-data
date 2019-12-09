/*
    incomprehensibility.hpp
    - incomprehensibility fitness

    Created by Sungwoo Jeon
    Modified by Juan Lee
*/

#include <string>
#include <vector>

#include "../wav/wav.hpp"

#ifndef __INCOMPREHENSIBILITY_HPP__
#define __INCOMPREHENSIBILITY_HPP__

/*
    Class incomprehensibility
    - Wave incomprehensibility
*/
class Incomprehensibility
{
private:
    std::vector<Wav> originals;
    float _fitness;
    float min_fitness;
    char smallest(char A, char B, char C);
    bool evaluateFitness(int sampleRate, Wav &original, Wav &modified);

public:
    Incomprehensibility(std::vector<Wav> &originals);
    bool evaluate(int sampleRate, Wav &modified);

    float fitness();
};

#endif