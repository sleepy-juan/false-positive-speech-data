#include "../ga/ga.hpp"
#include "../wav/wav.hpp"
#include <string>
#include <iostream>

int main(int argc, char ** argv){

    std::string bpath = "../../audio/original/weather.wav";
    std::string apath = "../../audio/modified/ga/";
    GA *ga;

    std::vector<Wav> wavs;

    for(int i=0;i<5;i++){
        Wav wav(bpath);
        wavs.push_back(wav);
    }


    int param1=0, param2=0, param4=0; 
    float param3=0.8, param5=0.1;
    

    if(argc == 6){

        int param1 = atoi(argv[1]);
        int param2 = atoi(argv[2]);
        float param3 = atof(argv[3]);
        int param4 = atoi(argv[4]);
        float param5 = atof(argv[5]);

    }else{
        std::cout << "parameter rule not matched. use default\n";
    }




    /*
        param1: selection algorithm
        param2: crossover operator
        param3: crossover rate
    */

    std::string selections[] = {"SELECT_ROULETTE", "SELECT_SUS"};
    std::string crossovers[] = {"CROSS_ONE_POINT", "CROSS_UNIFORM", "CROSS_ARITHMETIC"};
    std::string mutations[] = {"MUTATE_ADD_OR_SUB", "MUTATE_SWAP"};

    std::cout << "####### parameters #######" << std::endl;
    std::cout << "selection: " << selections[param1] << std::endl;
    std::cout << "crossover: " << crossovers[param2] << std::endl;
    std::cout << "     rate: " << param3 << std::endl;
    std::cout << " mutation: " << mutations[param4] << std::endl;
    std::cout << "     rate: " << param5 << std::endl;
    std::cout << "##########################" << std::endl;

    std::vector<Wav>& ret = ga->run(wavs, (GA::selection_operator) param1, (GA::crossover_operator) param2, param3, \
                                (GA::mutation_operator) param4, param5);

    for(int i=0;i<5;i++){
        ret[i].save(apath + std::to_string(i) + std::string(".wav"));
    }

    return 0;
}