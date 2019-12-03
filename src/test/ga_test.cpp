#include "../ga/ga.hpp"
#include "../wav/wav.hpp"
#include <string>
#include <iostream>

int main(int argc, char ** argv){

    std::string bpath = "../../audio/original/";
    std::string apath = "../../audio/modified/ga/";

    std::vector<Wav> wavs;
    int parentsSize = 20;

    for(int i=1;i<=parentsSize;i++){
        Wav wav(bpath + std::to_string(i) + std::string(".wav"));
        wavs.push_back(wav);
    }

    GA ga(wavs);
    std::vector<Wav>& ret = ga.run();

    for(int i=1;i<=ret.size();i++){
        ret[i-1].save(apath + std::to_string(i) + std::string(".wav"));
    }

    return 0;
}