#include "ga.hpp"
#include <random>
#include <iostream>


std::vector<Wav> parents;
std::vector<Fitness> fitnessOfParents;
std::vector<uint32_t> matingPool;
std::vector<Wav> offsprings;
std::vector<Fitness> fitnessOfOffsprings;

/* private method */
std::vector<Fitness> GA::evaluateFitness(std::vector<Wav> &wavs, float gamma){
    // call fitness evaluation function
}

std::vector<uint32_t> GA::select(int poolSize){

    std::vector<uint32_t> mating;
    mating.clear();

    // to be implemented
    for(int i=0;i<poolSize;i++)
        mating.push_back(i);

    return mating;
}

Wav GA::crossover(Wav &parent1, Wav &parent2){
    
    // to be implemented
    Wav w("../../audio/original/weather.wav");
    return w;
}

void GA::mutate(Wav &offspring){

    // amount of byte to mutate
    uint32_t mutateLength = 100000;
    uint8_t mutateAmount = 255;

    // set random
    std::random_device rd;
    std::mt19937 mersenne(rd());
    uint32_t wavSize = offspring.size();
    std::uniform_int_distribution<> byte(0, wavSize-mutateLength);

    // find location to mutate
    uint32_t locationToMutate = byte(mersenne);
    std::vector<uint8_t> mutant = offspring.get();
    
    // add or subtract small amount of integer
    for(int i=0;i<mutateLength;i++){
        if(mutant[locationToMutate + i] <= UINT8_MAX - mutateAmount)
            mutant[locationToMutate + i] = mutant[locationToMutate + i] + mutateAmount;
        else
            mutant[locationToMutate + i] = UINT8_MAX;
    }
    
    // mutate
    offspring.set(mutant);


}


std::vector<Wav>& GA::run(std::vector<Wav>& wavs){

    
    // parameters
    int maxGeneration = 1;
    int numPopulation = wavs.size();
    int numMatingPool = 20;
    int numElite = 0;
    int crossoverRate = 0;
    int mutateRate = 1;

    // set random
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<> mate(0, numMatingPool);
    std::uniform_real_distribution<> prob(0, 1);

    
    // initialize
    parents.assign(wavs.begin(), wavs.end());
    offsprings.clear();
    fitnessOfParents.clear();
    fitnessOfOffsprings.clear();
    matingPool.clear();
        
    // run ga
    for(int j=1;j<=maxGeneration;j++){

        
        fitnessOfParents = evaluateFitness(parents, 1);
        
        // roulette wheel
        matingPool = select(numMatingPool);
        
        
        // crossover
        for(int i=0;i<numPopulation-numElite;i++){

            int p1 = mate(mersenne), p2;
            do{
                p2 = mate(mersenne);
            }while(p1 == p2);

            offsprings.push_back(crossover(parents[matingPool[p1]], parents[matingPool[p2]]));
        }

        // elitism - to be implemented
        
        
        // mutation
        for(int i=0;i<numPopulation;i++){
            int rate = prob(mersenne);
            if(rate < mutateRate){
                mutate(offsprings[i]);
            }
            
        }
    

        parents.assign(offsprings.begin(), offsprings.end());
        

       

    }
    

    return parents;

}