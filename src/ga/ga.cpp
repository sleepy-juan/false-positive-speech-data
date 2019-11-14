#include "ga.hpp"
#include <iostream>
#include <random>


std::vector<Wav> parents;                       // Wav vector for parent
std::vector<Fitness> fitnessOfParents;          // Fitness vector of each corresponding parent
std::vector<uint32_t> matingPool;               // Selected parents' index by selection algorithm
std::vector<Wav> offsprings;                    // Wav vector made by parents(crossover, mutation ...)

std::random_device rd;                          // for random function
std::mt19937 mersenne(rd());

/* private method */
std::vector<Fitness> GA::evaluateFitness(std::vector<Wav> &wavs, float gamma){
    // call fitness evaluation function

    std::vector<Fitness> v(wavs.size(), 0);
    return v;

    // return Fitness(wavs, gamma);
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
    
    
    std::vector<uint8_t> wav1 = parent1.get();
    std::vector<uint8_t> wav2 = parent2.get();
    
    std::uniform_int_distribution<> points(0, wav1.size()-1);

    int crossoverPoint = points(mersenne);
    
    Wav w("../../audio/original/weather.wav");
    w.set(wav1);
    w.replace(crossoverPoint, parent2.range(crossoverPoint, wav1.size()));

    //w.set(offspring);

    return w;
}

void GA::mutate(Wav &offspring){

    // amount of byte to mutate
    uint32_t mutateLength = 100000;
    uint8_t mutateAmount = 255;

    // set random
    uint32_t wavSize = offspring.size();
    std::uniform_int_distribution<> byte(0, wavSize-mutateLength-1);
    std::uniform_int_distribution<> addorsub(0, 1);                     // 0: addition & 1: substraction

    // find location to mutate
    uint32_t locationToMutate = byte(mersenne);
    std::vector<uint8_t> mutant = offspring.get();
    
    // add or subtract small amount of integer
    if(addorsub(mersenne) == 0){
        for(int i=0;i<mutateLength;i++){
            if(mutant[locationToMutate + i] <= UINT8_MAX - mutateAmount)
                mutant[locationToMutate + i] = mutant[locationToMutate + i] + mutateAmount;
            else
                mutant[locationToMutate + i] = UINT8_MAX;
        }
    }else{
        for(int i=0;i<mutateLength;i++){
            if(mutant[locationToMutate + i] > mutateAmount)
                mutant[locationToMutate + i] = mutant[locationToMutate + i] - mutateAmount;
            else
                mutant[locationToMutate + i] = 0;
        }
    }
    
    // mutate
    offspring.set(mutant);


}


std::vector<Wav>& GA::run(std::vector<Wav>& wavs){

    
    // parameters
    int maxGeneration = 10;
    int numPopulation = wavs.size();
    int numMatingPool = 5;
    int numElite = 0;
    int crossoverRate = 0;
    int mutateRate = 1;

    // set random
    std::uniform_int_distribution<> mate(0, numMatingPool-1);
    std::uniform_real_distribution<> prob(0, 1);

    
    // initialize
    parents.assign(wavs.begin(), wavs.end());
    offsprings.clear();
    fitnessOfParents.clear();
    matingPool.clear();
        
    // run ga
    for(int j=1;j<=maxGeneration;j++){

        std::cout << "generation: " << j << std::endl;
        
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