/*
    ga.hpp

    Created by Kihoon Kwon
*/

#ifndef __GA_HPP__
#define __GA_HPP__

#include "../fitness/incomprehensibility.hpp"
#include "../wav/wav.hpp"
#include <vector>
#include <random>


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

    std::vector<Wav>& run();

    GA(std::vector<Wav>& wavs, selection_operator op1, crossover_operator op2, float crossoverRate, \
                        mutation_operator op3, float mutationRate);

    ~GA();

private:

    /* parameters */
    int maxGeneration;
    int numPopulation;
    int numMatingPool;
    int numElite;

    /* fitness evaluation */
    Incomprehensibility* fitfunc;
    Fitness sumOfFitness;

    /* selection */
    selection_operator opSelect;

    /* crossover*/
    crossover_operator opCross;
    float crossoverRate;

    /* mutation */
    mutation_operator opMutate;
    float mutationRate;
    uint8_t mutateAmount;


    /* private vectors */
    std::vector<Wav> parents;                       // Wav vector for parent
    std::vector<Fitness> fitnessOfParents;          // Fitness vector of each corresponding parent
    std::vector<uint32_t> matingPool;               // Selected parents' index by selection algorithm
    std::vector<Wav> offsprings;                    // Wav vector made by parents(crossover, mutation, etc)

    /* private method */
    void evaluateFitness();
    void select();
    void crossover(int p1, int p2);
    void mutate(Wav &offspring);

    //std::vector<Wav> nonDominatedSort();
    //std::vector<Wav> crowdingDistanceSort(std::vector<Wav>& sorted);



};


#endif