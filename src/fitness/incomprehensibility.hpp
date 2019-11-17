/*
    incomprehensibility.hpp
    - incomprehensibility fitness

    Created by Sungwoo Jeon
*/

#include <string>

#include "../wav/wav.hpp"

/*
    Class incomprehensibility
    - Wave incomprehensibility
*/
class Incomprehensibility
{
private:
    Wav original;
    Wav modified;
    int sampleRate;
    float _fitness;

public:
    Incomprehensibility(Wav &original, Wav &modified);
    bool evaluateFitness();

    float fitness();
    void changeSample(int newRate);
};

char smallest(char A, char B, char C);
