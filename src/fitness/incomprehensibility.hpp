/*
    incomprehensibility.hpp
    - incomprehensibility fitness

    Created by Sungwoo Jeon
    Modified by Juan Lee
*/

#include <string>

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
    Wav original;
    Wav modified;
    float _fitness;

    char smallest(char A, char B, char C);

public:
    Incomprehensibility(Wav &original, Wav &modified);
    bool evaluate(int sampleRate);

    float fitness();
};

#endif