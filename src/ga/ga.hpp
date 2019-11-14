/*
    ga.hpp

    Created by Kihoon Kwon
*/

#ifndef __GA_HPP__
#define __GA_HPP__

#include "../wav/wav.hpp"
#include <vector>


typedef float Fitness;

class GA {

private:

    /* private method */
    std::vector<Fitness> evaluateFitness(std::vector<Wav> &wavs, float gamma);
    std::vector<uint32_t> select(int poolSize);
    Wav crossover(Wav &parent1, Wav &parent2);
    void mutate(Wav &offspring);

    //std::vector<Wav> nonDominatedSort();
    //std::vector<Wav> crowdingDistanceSort(std::vector<Wav>& sorted);



public:

    std::vector<Wav>& run(std::vector<Wav>& wavs);

};


#endif