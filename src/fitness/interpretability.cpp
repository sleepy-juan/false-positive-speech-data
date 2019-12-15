/*
    interpretability.cpp
    - interpretability fitness
    - Synchronize Google Speech API and calculate the differences

    Created by Juan Lee
*/

#include "interpretability.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <string>

#include <sstream>

Interpretability::Interpretability(Wav &wav, std::string original)
    : wav(wav), original(original), _transcript(""), _executed(false) {}

bool Interpretability::interpret(std::string path_to_apikey, std::string path_to_python)
{
    if (this->_executed)
        return true;

    int pipes[2];
    if (pipe(pipes) == -1)
    {
        return false;
    }

    int pid = fork();
    if (pid == 0)
    {
        close(1); // close stdout
        close(pipes[0]);
        dup2(pipes[1], 1); // duplicate

        std::string command = "export GOOGLE_APPLICATION_CREDENTIALS=";
        command += path_to_apikey;
        command += " && ";
        command += "python3 ";
        command += path_to_python;
        command += " ";
        command += wav.filename();
        command += " ";
        command += std::to_string(wav.sampleRate());

        system(command.c_str());
        exit(0);
    }
    else
    {
        close(pipes[1]);
        wait(NULL);

        try
        {
            char buf[1024] = {0};
            read(pipes[0], buf, 1024);
            std::stringstream ss(buf);

            std::getline(ss, this->_transcript);

            std::string tmp_confidence;
            std::getline(ss, tmp_confidence);

            std::cout << "python said \"" << this->_transcript << "\" and \"" << tmp_confidence << "\"" << std::endl;

            this->_confidence = std::stof(tmp_confidence);
        }
        catch (std::exception &e)
        {
            this->_transcript = "";
            this->_confidence = 0;
            return false;
        }
    }

    this->_executed = true;
    return true;
}

std::string Interpretability::transcript()
{
    transform(this->_transcript.begin(), this->_transcript.end(), this->_transcript.begin(), ::tolower);
    return this->_transcript;
}

float Interpretability::confidence()
{
    return this->_confidence;
}

float Interpretability::fitness()
{
    transform(this->_transcript.begin(), this->_transcript.end(), this->_transcript.begin(), ::tolower);
    transform(this->original.begin(), this->original.end(), this->original.begin(), ::tolower);

    float binary = (this->_transcript) == (this->original) ? 1 : 0;
    return binary * this->_confidence;
}

bool Interpretability::executed()
{
    return this->_executed;
}