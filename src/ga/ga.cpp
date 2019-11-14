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

    std::vector<Fitness> v(wavs.size(), 1);
    std::uniform_real_distribution<> prob(0, 1);
    int sz = wavs.size();

    for(int i = 0;i<sz;i++)
        v[i] = prob(mersenne);

    return v;

    // return Fitness(wavs, gamma);
}

std::vector<uint32_t> GA::select(int poolSize, selection_operator op){

    std::vector<uint32_t> mating(poolSize);
    std::uniform_real_distribution<> prob(0, 1);
    Fitness sumOfFitness = 0, currentFitnessSum = 0;
    int parentSize = parents.size();

    for(int i=0;i<fitnessOfParents.size();i++){
        sumOfFitness += fitnessOfParents[i];
    }

    Fitness pin, interval;
    int poolCount = 0;

    switch(op){
        /* Roulette Wheel Sampling */
        case SELECT_ROULETTE:
            while(poolCount < poolSize){
                
                int idx=0;
                pin = prob(mersenne) * sumOfFitness;
                currentFitnessSum = fitnessOfParents[idx];

                while(currentFitnessSum < pin){
                    currentFitnessSum += fitnessOfParents[++idx];
                }
                
                mating[poolCount++] = idx;
            }

            break;

        /* Stochastic Universal Sampling */
        case SELECT_SUS:
            pin = interval = sumOfFitness / (Fitness) poolSize;
            pin *= prob(mersenne);

            for(int i=0;i<parentSize;i++){
                currentFitnessSum += fitnessOfParents[i];
                while(currentFitnessSum > pin && poolCount < poolSize){
                    mating[poolCount++] = i;
                    pin += interval;
                }
            }

            while(poolCount < poolSize){
                mating[poolCount ++] += parentSize-1;
            }
            break;
    }

    /* debug 
    for(auto x: mating){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    */

    return mating;
}

Wav GA::crossover(Wav &parent1, Wav &parent2, crossover_operator op, float rate){
    
    
    std::vector<uint8_t> wav1 = parent1.get();
    std::vector<uint8_t> wav2 = parent2.get();
    std::vector<uint8_t> newWav;
    int waveSize = wav1.size();
    int crossoverPoint;
    Wav w("../../audio/original/weather.wav");

    std::uniform_int_distribution<> points(0, waveSize-1);
    std::uniform_real_distribution<> cross(0, 1);

    switch(op){
        case CROSS_ONE_POINT:
            crossoverPoint = points(mersenne);
            w.set(wav1);
            w.replace(crossoverPoint, parent2.range(crossoverPoint, wav1.size()));
            break;
        case CROSS_UNIFORM:
            newWav.assign(wav1.begin(), wav1.end());
            for(int i=0; i<waveSize;i++){
                if(cross(mersenne) > rate)
                    newWav[i] = wav2[i];
            }
            w.set(newWav);
            break;
        case CROSS_ARITHMETIC:
            newWav.assign(wav1.begin(), wav1.end());
            for(int i=0; i<waveSize;i++){
                newWav[i] = (newWav[i] + wav2[i]) / (float) 2;
            }
            w.set(newWav);
            break;
    }

    /* debug */
    // std::cout << "size: " << w.size() << std::endl;

    return w;
}

void GA::mutate(Wav &offspring, mutation_operator op){

    // amount of byte to mutate
    uint32_t mutateLength = 5000;
    uint8_t mutateAmount = 50;

    // set random
    uint32_t wavSize = offspring.size();
    std::uniform_int_distribution<> byte(0, wavSize-mutateLength-1);
    std::uniform_int_distribution<> addorsub(0, 1);                     // 0: addition & 1: substraction

    // find location to mutate
    uint32_t locationToMutate = byte(mersenne);
    std::vector<uint8_t> mutant = offspring.get();

    switch(op){
        case MUTATE_SWAP:
            // to be implemented
        case MUTATE_ADD_OR_SUB:
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
            break;            
    }
        
    // mutate
    offspring.set(mutant);


}


std::vector<Wav>& GA::run(std::vector<Wav>& wavs, selection_operator op1, crossover_operator op2, float crossoverRate, \
                        mutation_operator op3, float mutationRate){

    
    // parameters
    int maxGeneration = 100;
    int numPopulation = wavs.size();
    int numMatingPool = 5;
    int numElite = 0;
    //int crossoverRate = 0;
    //int mutationRate = 1;

    // set random
    std::uniform_int_distribution<> mate(0, numMatingPool-1);
    std::uniform_real_distribution<> prob(0, 1);

    
    // initialize
    parents.assign(wavs.begin(), wavs.end());
        
    // run ga
    for(int j=1;j<=maxGeneration;j++){

        std::cout << "generation: " << j << std::endl;

        offsprings.clear();
        fitnessOfParents.clear();
        matingPool.clear();
        
        fitnessOfParents = evaluateFitness(parents, 1);
        
        /* Select Fitter Individual as Parents */
        matingPool = select(numMatingPool, op1);
        
        // Crossover
        for(int i=0;i<numPopulation-numElite;i++){

            int p1 = mate(mersenne), p2;
            do{
                p2 = mate(mersenne);
            }while(p1 == p2);

            offsprings.push_back(crossover(parents[matingPool[p1]], parents[matingPool[p2]],\
                                             op2, crossoverRate));
        }

        // elitism - to be implemented
        
        
        // mutation
        for(int i=0;i<numPopulation;i++){
            int rate = prob(mersenne);
            if(rate < mutationRate){
                mutate(offsprings[i], op3);
            }
            
        }
    

        parents.assign(offsprings.begin(), offsprings.end());

    }
    

    return parents;

}