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

Incomprehensibility::Incomprehensibility(int n_originalWave, string originPath, vector<Wav> &modified)
    : n_originalWave(n_originalWave), originPath(originPath), modified(modified), _fitness(){}

bool Incomprehensibility::evaluate()
{
  vector<float> fitness;

  for (unsigned int i = 0; i < this->modified.size(); i++){
    vector<uint8_t> modifiedData = this->modified.at(i).get();

    float min_fitness = -1;

    for (int j = 0; j < this->n_originalWave; j++){
      string filename;
      filename = originPath + "/original" + to_string(j) + ".wav";

      vector<uint8_t> originalData;
      originalData = Wav(filename).get();
    }

    /* beta[i]: speechTotext interpretability of modified[i] */

    // beta.at(i) = interpretability(modified.at(i));
  }

  this->_fitness = fitness;
  return true;
}

vector<float> Incomprehensibility::fitness()
{
  return this->_fitness;
}

int main()
{
    return 0;
}