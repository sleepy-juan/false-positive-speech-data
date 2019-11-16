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
    Wav &original;
    Wav &modified;

    float _fitness;
    
public:
    Incomprehensibility(Wav &original, Wav &modified);
    bool evaluate(); 

    float fitness();
};
