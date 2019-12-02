/*
    unittest.cpp

    Created by Juan Lee
*/

#include <iostream>
#include <vector>

using namespace std;

#include "../wav/wav.hpp"

int main(int argc, char **argv)
{
    Wav wav("../../audio/original/1.wav");

    cout << wav.numberOfChannel() << endl;
    cout << wav.sampleRate() << endl;
    cout << wav.byteRate() << endl;
    cout << wav.blockAlign() << endl;
    cout << wav.bitPerSample() << endl;

    vector<uint8_t> data = wav.get();

    const int length = data.size() / 2;
    for (int i = 0; i < length; i++)
    {
        cout << i << endl;
        data.push_back(data.at(i));
    }
    wav.set(data);
    wav.save("modifed.wav");

    return 0;
}