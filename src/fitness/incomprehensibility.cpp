/*
    incomprehensibility.cpp
    - incomprehensibility fitness

    Created by Sungwoo Jeon
*/

#include "incomprehensibility.hpp"

#include <iostream>
#include <stdlib.h>

using namespace std;

Incomprehensibility::Incomprehensibility(Wav &original, Wav &modified)
    : original(original), modified(modified), sampleRate(200), _fitness(0) {}

bool Incomprehensibility::evaluateFitness()
{
  float fitness = 0;

  vector<uint8_t> originalData = original.get();
  vector<uint8_t> modifiedData = modified.get();
  
  int numRows = originalData.size() / sampleRate;
  int numCols = modifiedData.size() / sampleRate;

  uint8_t DTW[numRows][numCols] = { 0, };

  /* Fill DTW matrix */
  DTW[0][0] = abs(originalData.at(0) - modifiedData.at(0));
  for (int i = 1; i < numRows; i++){
    DTW[i][0] = DTW[i - 1][0] + abs(originalData.at(i * sampleRate) - modifiedData.at(0));
  }
  for (int j = 1; j < numCols; j++){
    DTW[0][j] = DTW[0][j - 1] + abs(modifiedData.at(j * sampleRate) - originalData.at(0));
  }
  for (int i = 1; i < numRows; i++){
    for (int j = 1; j < numCols; j++){
      DTW[i][j] = abs(originalData.at(i * sampleRate) - modifiedData.at(j * sampleRate)) + biggest(DTW[i - 1][j], DTW[i][j - 1], DTW[i - 1][j - 1]);
    }
  }


  this->_fitness = fitness;
  return true;
}

float Incomprehensibility::fitness()
{
  return this->_fitness;
}

void Incomprehensibility::changeSample(int newRate)
{
  this->sampleRate = newRate;
}

char biggest(char A, char B, char C)
{
  if (A >= B && A >= C){
    return A;
  }
  if (B >= A && B >= C){
    return B;
  }
  return C;
}

int main()
{
  char a = 10;
  char b = 16;

  std::cout << abs(a-b) << std::endl;

  return 0;
}