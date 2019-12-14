/*
    simulator.cpp
    - main runnable code for the entire project
    - combine the components, ga w/ fitnesses, human in the loop, and codes for evaluation

    Created by Juan Lee
*/

#include "ga/ga.hpp"
#include "wav/wav.hpp"

/* main function */
int main()
{
    std::string bpath = "../audio/original/";
    std::string apath = "../audio/modified/ga/";

    std::vector<Wav> wavs;
    int parentsSize = 5;

    for (int i = 1; i <= parentsSize; i++)
    {
        Wav wav(bpath + std::to_string(i) + std::string(".wav"));
        wavs.push_back(wav);
    }

    GA ga(wavs);
    std::vector<Wav> &ret = ga.run();

    for (int i = 1; i <= ret.size(); i++)
    {
        ret[i - 1].save(apath + std::to_string(i) + std::string(".wav"));
    }

    return 0;
}