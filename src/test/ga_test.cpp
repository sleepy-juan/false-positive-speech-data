#include "../ga/ga.hpp"
#include "../wav/wav.hpp"
#include <string>

int main(){

    std::string bpath = "../../audio/original/weather.wav";
    std::string apath = "../../audio/modified/ga/";
    GA *ga;

    std::vector<Wav> wavs;
    
    for(int i=0;i<5;i++){
        Wav wav(bpath);
        wavs.push_back(wav);
    }
    
    std::vector<Wav>& ret = ga->run(wavs);

    for(int i=0;i<5;i++){
        ret[i].save(apath + std::to_string(i) + std::string(".wav"));
    }

    return 0;
}