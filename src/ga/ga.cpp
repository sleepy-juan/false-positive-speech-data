#include "ga.hpp"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

/* random */
std::random_device rd;  // for random function
std::mt19937 mersenne(rd());

/* private method */
void GA::evaluateFitness(){
    // call fitness evaluation function 

    int parentSize = this->parents.size();
    this->fitnessOfParents.assign(parentSize, 0);
    this->sumOfFitness = 0;

    for(int i=0;i<parentSize;i++){
        if(this->fitfunc->evaluate(200, this->parents[i])){
            this->fitnessOfParents[i] = this->fitfunc->fitness() + 0.0001;
        }
        
        this->sumOfFitness += this->fitnessOfParents[i];

        //printf("fitness%d : %f\n", i, this->fitnessOfParents[i]);
    }

}

void GA::select(){

    this->matingPool.assign(this->numMatingPool, NULL);

    std::uniform_real_distribution<> prob(0, 1);
    float p;
    Fitness currentFitnessSum = 0;

    int parentSize = parents.size();

    Fitness pin, interval;
    int poolCount = 0;

    switch(this->opSelect){
        /* Roulette Wheel Sampling */
        case SELECT_ROULETTE:
            while(poolCount < this->numMatingPool){
                
                int idx=0;
                pin = prob(mersenne) * this->sumOfFitness;
                currentFitnessSum = this->fitnessOfParents[idx];

                while(currentFitnessSum < pin){
                    currentFitnessSum += this->fitnessOfParents[++idx];
                }
                
                this->matingPool[poolCount++] = idx;
            }

            break;

        /* Stochastic Universal Sampling */
        case SELECT_SUS:
            pin = interval = this->sumOfFitness / (Fitness) this->numMatingPool;

            do{
                p = prob(mersenne);
            }while(p == 0);

            pin *= p;

            for(int i=0;i<parentSize;i++){
                currentFitnessSum += fitnessOfParents[i];
                while(currentFitnessSum > pin && poolCount < this->numMatingPool){
                    this->matingPool[poolCount++] = i;
                    pin += interval;
                }
            }

            while(poolCount < this->numMatingPool){
                this->matingPool[poolCount ++] += parentSize-1;
            }
            break;
    }

    /* debug 
    for(auto x: this->matingPool){
        std::cout << x << " ";
    }
    std::cout << std::endl;
    */
    
}

void GA::crossover(int parent1, int parent2){
    
    
    std::vector<uint8_t> wav1 = this->parents[parent1].get();
    std::vector<uint8_t> wav2 = this->parents[parent2].get();
    std::vector<uint8_t> child;

    int bps = this->parents[parent1].bitPerSample();
    int wav1Size = wav1.size() / bps;
    int wav2Size = wav2.size() / bps;

    int wav1Point, wav2Point;
    Wav w1(this->parents[parent1].filename());
    Wav w2(this->parents[parent2].filename());

    std::uniform_real_distribution<> points(0, 1);
    std::uniform_real_distribution<> cross(0, 1);
    float p;

    switch(this->opCross){
        case CROSS_ONE_POINT:

            p = points(mersenne);

            wav1Point = (int) (p * wav1Size);
            wav2Point = (int) (p * wav2Size);

            child.clear();

            for(int i=0;i<wav1Point;i++)
                for(int j=0;j<bps;j++)
                    child.push_back(wav1[bps*i + j]);
            
            for(int i=wav1Point;i<wav1Size;i++)
                for(int j=0;j<bps;j++){
                    int idx = (int) (i * wav2Size / wav1Size) * bps + j;
                    if(idx < wav2.size())
                        child.push_back(wav2[idx]);
                    else
                        child.push_back(0);
                }

            w1.set(child);
            
            if(w1.valid())
                this->offsprings.push_back(w1);

            if(this->offsprings.size() < this->numPopulation - this->numElite){

                child.clear();

                for(int i=0;i<wav2Point;i++)
                    for(int j=0;j<bps;j++)
                        child.push_back(wav2[bps*i + j]);

                for(int i=wav2Point;i<wav2Size;i++)
                    for(int j=0;j<bps;j++){
                        int idx = (int) (i * wav1Size / wav2Size) * bps + j;
                        if(idx < wav1.size())
                            child.push_back(wav1[idx]);
                        else
                            child.push_back(0);
                    }

                w2.set(child);
                
                if(w2.valid())
                    this->offsprings.push_back(w2);
            }

            break;
        case CROSS_UNIFORM:
            break;
        case CROSS_ARITHMETIC:
            break;
    }

    /* debug */
    //std::cout << "size: " << w2.get().size() << std::endl;
}

void GA::mutate(Wav &offspring){

    // amount of byte to mutate
    //uint32_t mutateLength = 5000;

    // set random
    //std::uniform_int_distribution<> byte(0, wavSize-mutateLength-1);

    std::uniform_real_distribution<> mrate(0, 1);
    std::uniform_int_distribution<> addorsub(0, 1);     // 0: addition & 1: substraction

    // find location to mutate
    //uint32_t locationToMutate = byte(mersenne);
    std::vector<uint8_t> mutant = offspring.get();
    std::vector<uint8_t> backup = offspring.get();
    int bps = offspring.bitPerSample();
    int wavSize = mutant.size() / bps;

    switch(this->opMutate){
        case MUTATE_ADD_OR_SUB:
            // add or subtract small amount of integer
            for(int i=0;i<wavSize;i++){
                float doRate = mrate(mersenne);
                if(this->mutationRate > doRate){
                    if(addorsub(mersenne)==0){
                        for(int j=0;j<bps;j++){
                            if(mutant[i*bps + j] + this->mutateAmount > mutant[i*bps + j])
                                mutant[i*bps + j] = mutant[i*bps + j] + this->mutateAmount;
                            else
                                mutant[i*bps + j] = UINT8_MAX;
                        }
                    }else{
                        for(int j=0;j<bps;j++){
                            if(mutant[i*bps + j] - this->mutateAmount < mutant[i*bps + j])
                                mutant[i*bps + j] = mutant[i*bps + j] - this->mutateAmount;
                            else
                                mutant[i*bps + j] = 0;
                        } 
                    }

                }
                //printf("doRate: %f\n", doRate);
            }

                
            break;     
        case MUTATE_SWAP:
            // to be implemented   
            break;    
    }
        
    // mutate
    offspring.set(mutant);

    if(!offspring.valid())
        offspring.set(backup);


}

GA::GA(std::vector<Wav>& wavs){

    /* population */
    this->numPopulation = wavs.size();

    /* fitness evaluation */
    this->fitfunc = new Incomprehensibility(wavs);
    this->sumOfFitness = 0;


    std::cout << "####### parameters #######" << std::endl;
    std::string selections[] = {"SELECT_ROULETTE", "SELECT_SUS"};
    std::string crossovers[] = {"CROSS_ONE_POINT", "CROSS_UNIFORM", "CROSS_ARITHMETIC"};
    std::string mutations[] = {"MUTATE_ADD_OR_SUB", "MUTATE_SWAP"};

    int numOfParameters = 9;
    std::ifstream f("../ga/parameters.csv");
    std::string params;
    std::vector<std::string> args(numOfParameters);

    /* parameter parsing from csv file */
    for(int i=0;i<numOfParameters;i++){
        getline(f, params, ',');
        getline(f, params);
        args[i] = params;
    }

    /* generation */
    this->maxGeneration = stoi(args[0]);
    this->numMatingPool = stoi(args[1]);
    this->numElite = stoi(args[2]);

    /* selection */
    this->opSelect = (selection_operator) stoi(args[3]);

    /* crossover*/
    this->opCross = (crossover_operator) stoi(args[4]);
    this->crossoverRate = stof(args[5]);

    /* mutation*/
    this->opMutate = (mutation_operator) stoi(args[6]);
    this->mutationRate = stof(args[7]);
    this->mutateAmount = stoi(args[8]);
    
    std::cout << "generation: " << this->maxGeneration << std::endl;
    std::cout << "population: " << this->numPopulation << std::endl;
    std::cout << "    mating: " << this->numMatingPool << std::endl;
    std::cout << "     elite: " << this->numElite << std::endl;
    std::cout << " selection: " << selections[this->opSelect] << std::endl;
    std::cout << " crossover: " << crossovers[this->opCross] << std::endl;
    std::cout << "      rate: " << this->crossoverRate << std::endl;
    std::cout << "  mutation: " << mutations[this->opMutate] << std::endl;
    std::cout << "      rate: " << this->mutationRate << std::endl;
    std::cout << "    amount: " << this->mutateAmount << std::endl;
    std::cout << "##########################" << std::endl;


    /* vector initialize */
    this->parents.assign(wavs.begin(), wavs.end());
    this->fitnessOfParents.clear();
    this->matingPool.clear();
    this->offsprings.clear();
    
}

GA::~GA(){
    delete this->fitfunc;
}


std::vector<Wav>& GA::run(){

    // set random
    std::uniform_int_distribution<> mate(0, this->numMatingPool-1);
    std::uniform_real_distribution<> prob(0, 1);


    /* debug */
    
    // for(auto x: this->parents){
    //     std::cout << x.valid() << " ";
    // }
    // std::cout << std::endl;


    /* run ga */
    for(int j=1;j<=this->maxGeneration;j++){

        std::cout << "generation: " << j << std::endl;

        this->offsprings.clear();
        this->fitnessOfParents.clear();
        this->matingPool.clear();
        
        //std::cout << "fitness" << std::endl;
        this->evaluateFitness();

        /* Select Fitter Individual as Parents */
        //std::cout << "select" << std::endl;
        this->select();
        
        // Crossover
        //std::cout << "crossover" << std::endl;
        while(this->offsprings.size() < this->numPopulation - this->numElite){

            int p1 = mate(mersenne), p2;
            do{
                p2 = mate(mersenne);
            }while(p1 == p2);
            
            this->crossover(this->matingPool[p1], this->matingPool[p2]);
        }


    //     // elitism - to be implemented
        
        
         // mutation
         for(int i=0;i<this->numPopulation;i++){
             mutate(this->offsprings[i]);
         }
    

        this->parents.assign(this->offsprings.begin(), this->offsprings.end());

     }
    
    std::cout << "ga done" << std::endl;

    return this->parents;

}