/*
    incomprehensibility.hpp
    - incomprehensibility fitness
    - Calculate the difference of waves
      under the assumption that the bigger difference the waves are, the more difficult for people to understand

    Algorithm Designed by Sungwoo Jeon
    Code Written by Juan Lee
*/

#ifndef __INCOMPREHENSIBILITY_H__
#define __INCOMPREHENSIBILITY_H__

#include "../wav/wav.hpp"

/*
    Class Incomprehensiblity
    - Human Negative Comprehensiblity
*/
class Incomprehensibility
{
private:
public:
    Incomprehensibility(Wav &wav);
    float fitness();
    float normalizedFitness(float minimum, float maximum);
};

#endif