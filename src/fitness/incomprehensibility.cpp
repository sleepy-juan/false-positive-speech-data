/*
    incomprehensibility.cpp
    - incomprehensibility fitness

    Created by Sungwoo Jeon
*/

#include "incomprehensibility.hpp"

#include <iostream>
#include <stdlib.h>
#include <cmath>

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

  int DTW[numRows][numCols] = { 0, };

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
      DTW[i][j] = abs(originalData.at(i * sampleRate) - modifiedData.at(j * sampleRate)) + smallest(DTW[i - 1][j], DTW[i][j - 1], DTW[i - 1][j - 1]);
    }
  }

  int i = 0;
  int j = 0;
  int verticalPath = 0;
  int totalPath = 0;

  while (i != numRows && j != numCols){
    if (DTW[i + 1][j + 1] <= DTW[i + 1][j] && DTW[i + 1][j + 1] <= DTW[i][j + 1]){
      i += 1;
      j += 1;
    }
    else if (DTW[i][j + 1] <= DTW[i + 1][j + 1] && DTW[i][j + 1] <= DTW[i + 1][j]){
      if (DTW[i][j + 1] == DTW[i + 1][j] && i < j){
        i += 1;
        verticalPath += 1;
      }
      else{
        j += 1;
        verticalPath += 1;
      }
    }
    else{
      i += 1;
      verticalPath += 1;
    }
    totalPath += 1;
  }
  verticalPath += numRows + numCols - i - j;
  totalPath += numRows + numCols - i - j;
  
  fitness = sqrt((float) verticalPath / (float) totalPath);

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

char smallest(char a, char b, char c)
{
  if (a <= b && a <= c){
    return a;
  }
  else if (b <= a && b <= c){
    return b;
  }
  return c;
}
