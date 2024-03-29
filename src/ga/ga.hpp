/*
    ga.hpp

    Created by Kihoon Kwon
*/

#ifndef __GA_HPP__
#define __GA_HPP__

#include "../fitness/fitness.hpp"
#include "../wav/wav.hpp"
#include <vector>

class GA
{

public:
    enum selection_operator
    {
        SELECT_ROULETTE,
        SELECT_SUS
    };

    enum crossover_operator
    {
        CROSS_ONE_POINT,
        CROSS_UNIFORM,
        CROSS_ARITHMETIC
    };

    enum mutation_operator
    {
        MUTATE_ADD_OR_SUB,
        MUTATE_SWAP
    };

    std::vector<Wav> &run(int sg);
    std::vector<Wav> parents; // Wav vector for parent

    GA(std::vector<Wav> &wavs);

    ~GA();

private:
    /* parameters */
    int maxGeneration;
    int numPopulation;
    int numMatingPool;
    int numElite;

    /* fitness evaluation */
    Fitness *fitfunc;
    float sumOfFitness;

    /* selection */
    selection_operator opSelect;

    /* crossover*/
    crossover_operator opCross;
    float crossoverRate;

    /* mutation */
    mutation_operator opMutate;
    float mutationRate;
    int mutateAmount;

    /* private vectors */
    std::vector<float> fitnessOfParents; // Fitness vector of each corresponding parent
    std::vector<uint32_t> matingPool;    // Selected parents' index by selection algorithm
    std::vector<Wav> offsprings;         // Wav vector made by parents(crossover, mutation, etc)

    /* private method */
    void evaluateFitness();
    void select();
    void crossover(int p1, int p2);
    void mutate(Wav &offspring);
    void elitism();

    //std::vector<Wav> nonDominatedSort();
    //std::vector<Wav> crowdingDistanceSort(std::vector<Wav>& sorted);
};

#endif