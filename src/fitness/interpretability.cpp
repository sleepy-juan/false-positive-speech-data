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
        close(1);          // close stdout
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
        wait(NULL);

        char buf[1024] = {0};
        read(pipes[0], buf, 1024);
        std::stringstream ss(buf);

        std::getline(ss, this->_transcript);

        std::string tmp_confidence;
        std::getline(ss, tmp_confidence);

        this->_confidence = std::stof(tmp_confidence);
    }

    this->_executed = true;
    return true;
}

std::string Interpretability::transcript()
{
    return this->_transcript;
}

float Interpretability::confidence()
{
    return this->_confidence;
}

float Interpretability::fitness()
{
    float binary = this->_transcript == this->original ? 1 : 0;
    return binary * this->_confidence;
}

bool Interpretability::executed()
{
    return this->_executed;
}