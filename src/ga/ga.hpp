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

public:

    enum selection_operator{
        SELECT_ROULETTE,
        SELECT_SUS
    };

    enum crossover_operator{
        CROSS_ONE_POINT,
        CROSS_UNIFORM,
        CROSS_ARITHMETIC
    };

    enum mutation_operator{
        MUTATE_ADD_OR_SUB,
        MUTATE_SWAP
    };

    std::vector<Wav>& run(std::vector<Wav>& wavs, selection_operator op1, crossover_operator op2, float crossoverRate,\
                         mutation_operator op3, float mutationRate);

private:


    /* private method */
    std::vector<Fitness> evaluateFitness(std::vector<Wav> &wavs, float gamma);
    std::vector<uint32_t> select(int poolSize, selection_operator op);
    Wav crossover(Wav &parent1, Wav &parent2, crossover_operator op, float rate);
    void mutate(Wav &offspring, mutation_operator op);

    //std::vector<Wav> nonDominatedSort();
    //std::vector<Wav> crowdingDistanceSort(std::vector<Wav>& sorted);



};


#endif