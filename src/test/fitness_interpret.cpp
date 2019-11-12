/*
    wav.cpp

    Created by Juan Lee
*/

#include <iostream>
#include <vector>

#include "../wav/wav.hpp"
#include "../fitness/interpretability.hpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " wavfile" << std::endl;
        return -1;
    }

    Wav wav(argv[1]);
    Interpretability fitness(wav, "how's the weather today");

    bool result = fitness.interpret("../../google_api_key.json", "../fitness/google_api_python.py");
    if (!result)
    {
        std::cout << "Something went wrong!" << std::endl;
        return -1;
    }

    std::cout << fitness.transcript() << std::endl;
    std::cout << fitness.confidence() << std::endl;
    std::cout << fitness.fitness() << std::endl;

    // re-execute
    result = fitness.interpret("../../google_api_key.json", "../fitness/google_api_python.py");
    if (!result)
    {
        std::cout << "Something went wrong!" << std::endl;
        return -1;
    }

    std::cout << fitness.transcript() << std::endl;
    std::cout << fitness.confidence() << std::endl;
    std::cout << fitness.fitness() << std::endl;

    return 0;
}