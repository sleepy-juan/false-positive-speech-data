/*
    incomprehensibility.cpp
    - incomprehensibility fitness

    Created by Sungwoo Jeon
*/

#include "incomprehensibility.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sstream>

using namespace std;

Incomprehensibility::Incomprehensibility(Wav &original, Wav &modified)
    : original(original), modified(modified), _fitness(0) {}

bool Incomprehensibility::evaluate()
{
  float fitness;

  

  this->_fitness = fitness;
  return true;
}

float Incomprehensibility::fitness()
{
  return this->_fitness;
}

int main()
{
    return 0;
}