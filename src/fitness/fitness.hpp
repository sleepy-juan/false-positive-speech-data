/*
    fitness.hpp
    - fitness with incomprehensibility and interpretability

    Created by Sungwoo Jeon
*/

#include <string>

#include "../wav/wav.hpp"
#include "incomprehensibility.hpp"
#include "interpretability.hpp"

#ifndef __FITNESS_HPP__
#define __FITNESS_HPP__

/*
    Class fitness
    - Wave fitness for incomprehensibility and interpretability
*/
class Fitness
{
private:
    Wav wav1;
    Wav wav2;
    float ratio;

public:
    Fitness(Wav &wav1, Wav &wav2, float ratio);
    bool evaluate();

};

#endif