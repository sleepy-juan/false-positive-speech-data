/*
    incomprehensibility.cpp
    - incomprehensibility fitness

    Created by Sungwoo Jeon
*/

#include "incomprehensibility.hpp"

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cmath>

using namespace std;

Incomprehensibility::Incomprehensibility(std::vector<Wav> &originals)
    : originals(originals), _fitness(0) {}

bool Incomprehensibility::evaluateFitness(int sampleRate, Wav &original, Wav &modified)
{
  float fitness = 0;

  vector<uint8_t> originalData = original.get();
  vector<uint8_t> modifiedData = modified.get();

  int numRows = originalData.size() / sampleRate;
  int numCols = modifiedData.size() / sampleRate;

  /* Allocate DTW matrix memory */
  // int DTW[numRows][numCols] = { 0, };
  int **DTW = new int *[numRows];
  for (int i = 0; i < numRows; ++i)
  {
    DTW[i] = new int[numCols];
    memset(DTW[i], 0, sizeof(int) * numCols);
  }

  /* Fill DTW matrix */
  DTW[0][0] = abs(originalData.at(0) - modifiedData.at(0));
  for (int i = 1; i < numRows; i++)
  {
    DTW[i][0] = DTW[i - 1][0] + abs(originalData.at(i * sampleRate) - modifiedData.at(0));
  }
  for (int j = 1; j < numCols; j++)
  {
    DTW[0][j] = DTW[0][j - 1] + abs(modifiedData.at(j * sampleRate) - originalData.at(0));
  }
  for (int i = 1; i < numRows; i++)
  {
    for (int j = 1; j < numCols; j++)
    {
      DTW[i][j] = abs(originalData.at(i * sampleRate) - modifiedData.at(j * sampleRate)) + smallest(DTW[i - 1][j], DTW[i][j - 1], DTW[i - 1][j - 1]);
    }
  }

  int i = 0;
  int j = 0;
  int verticalPath = 0;
  int totalPath = 0;

  while (i != numRows && j != numCols)
  {
    if (DTW[i + 1][j + 1] <= DTW[i + 1][j] && DTW[i + 1][j + 1] <= DTW[i][j + 1])
    {
      i += 1;
      j += 1;
    }
    else if (DTW[i][j + 1] <= DTW[i + 1][j + 1] && DTW[i][j + 1] <= DTW[i + 1][j])
    {
      if (DTW[i][j + 1] == DTW[i + 1][j] && i < j)
      {
        i += 1;
        verticalPath += 1;
      }
      else
      {
        j += 1;
        verticalPath += 1;
      }
    }
    else
    {
      i += 1;
      verticalPath += 1;
    }
    totalPath += 1;
  }
  verticalPath += numRows + numCols - i - j;
  totalPath += numRows + numCols - i - j;

  fitness = sqrt((float)verticalPath / (float)totalPath);

  if (fitness < this->_fitness)
    this->_fitness = fitness;

  /* free memory for DTW matrix */
  for (int i = 0; i < numRows; ++i)
  {
    delete[] DTW[i];
  }
  delete[] DTW;

  return true;
}

bool Incomprehensibility::evaluate(int sampleRate, Wav &modified)
{
  for (Wav original : this->originals)
  {
    bool success = this->evaluateFitness(sampleRate, original, modified);
    if (!success)
      return false;
  }
  return true;
}

float Incomprehensibility::fitness()
{
  return this->_fitness;
}

char Incomprehensibility::smallest(char a, char b, char c)
{
  if (a <= b && a <= c)
  {
    return a;
  }
  else if (b <= a && b <= c)
  {
    return b;
  }
  return c;
}
