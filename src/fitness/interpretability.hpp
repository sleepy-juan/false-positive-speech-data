/*
    interpretability.hpp
    - interpretability fitness
    - Synchronize Google Speech API and calculate the differences

    Created by Juan Lee
*/

#ifndef __INTERPRETABILITY_H__
#define __INTERPRETABILITY_H__

#include <string>

#include "../wav/wav.hpp"

/*
    Class Interpretability
    - Machine Interpretability
*/
class Interpretability
{
private:
    std::string original;
    std::string _transcript;
    float _confidence;
    Wav wav;

    bool _executed; // a flag indicating API executed or not

public:
    Interpretability(Wav &wav, std::string original);
    bool interpret(std::string path_to_apikey, std::string path_to_python); // call only once

    std::string transcript();
    float confidence();
    float fitness();

    bool executed();
};

#endif