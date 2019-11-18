/*
    fitness.cpp
    - fitness with incomprehensibility and interpretability

    Created by Sungwoo Jeon
*/

#include "fitness.hpp"


Fitness::Fitness(std::vector<Wav> &originals)
    : originals(originals), _fitness(0), gamma(0.5), sampleRate(100), path_to_apikey(""), path_to_python("") {}

bool Fitness::evaluate(Wav &wav)
{
    Incomprehensibility incomprehensibility(originals);
    if (!incomprehensibility.evaluate(sampleRate, wav))
    {
        return false;
    }

    Interpretability interpretability(wav, "ok google");
    if (!interpretability.interpret(path_to_apikey, path_to_python))
    {
        return false;
    }
    this->_fitness = incomprehensibility.fitness() * gamma + interpretability.fitness() * (1 - gamma);

    return true;
        
}

void Fitness::changeGamma(float newGamma)
{
    this->gamma = newGamma;
}

void Fitness::changeRate(int newRate)
{
    this->sampleRate = newRate;
}

float Fitness::fitness()
{
    return this->_fitness;
}