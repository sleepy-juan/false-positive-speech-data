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
    std::vector<Wav> originals;
    float _fitness;
    float gamma;
    int sampleRate;
    std::string path_to_apikey;
    std::string path_to_python;

public:
    Fitness(std::vector<Wav>& originals);
    bool evaluate(Wav &wav);
    void changeGamma(float newGamma);
    void changeRate(int newRate);
    float fitness();
};

#endif