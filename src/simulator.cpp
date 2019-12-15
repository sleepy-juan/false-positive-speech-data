/*
    simulator.cpp
    - main runnable code for the entire project
    - combine the components, ga w/ fitnesses, human in the loop, and codes for evaluation

    Created by Juan Lee
*/

#include "ga/ga.hpp"
#include "wav/wav.hpp"

#include <string>
#include <iostream>
using namespace std;

/* main function */
int main(int argc, char *argv[])
{
    int starting = 1;
    if (argc == 2)
    {
        starting = std::stoi(argv[1]);
    }

    // std::string bpath = "../audio/original/";
    std::string bpath = "../audio/modified/ga/g" + std::to_string(starting) + "_";
    std::string opath = "../audio/original/";
    std::string apath = "../audio/modified/ga/";

    std::vector<Wav> wavs;
    std::vector<Wav> bwavs;
    int parentsSize = 20;

    for (int i = 1; i <= parentsSize; i++)
    {
        Wav wav(opath + std::to_string(i) + std::string(".wav"));
        wavs.push_back(wav);

        if (starting != 1)
        {
            Wav bwav(bpath + std::to_string(i) + std::string(".wav"));
            bwavs.push_back(bwav);
        }
    }

    GA ga(wavs);
    if (starting != 1)
    {
        ga.parents.clear();
        ga.parents.assign(bwavs.begin(), bwavs.end());
    }

    // std::cout << "Ga start" << std::endl;

    std::vector<Wav> &ret = ga.run(starting);

    for (int i = 1; i <= ret.size(); i++)
    {
        std::cout << "save to " << apath + std::to_string(i) + std::string(".wav") << std::endl;
        ret[i - 1].save(apath + std::to_string(i) + std::string(".wav"));
    }

    return 0;
}