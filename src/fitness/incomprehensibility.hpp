/*
    incomprehensibility.hpp
    - incimprehensibility fitness

    Created by Sungwoo Jeon
*/

#include <string>
#include <vector>

#include "../wav/wav.hpp"

using namespace std;

/*
    Class incomprehensibility
    - Wave incomprehensibility
*/
class Incomprehensibility
{
private:
    int n_originalWave;
    string originPath;
    vector<Wav> &modified;
    vector<float> _fitness;

public:
    Incomprehensibility(int n_originalWave, string originPath, vector<Wav> &modified);
    bool evaluate(); 

    vector<float> fitness();
};
