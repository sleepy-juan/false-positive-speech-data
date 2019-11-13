#include <iostream>
#include <vector>
#include <string>
#include <wav.hpp>
#include <cmath>

using namespace std;

/* n: number of original file */
/* modified: vector of Wav classes */
/* ratio: fitness ratio*/
vector<float> Fitness(int n, vector<Wav>& modified, float ratio){

  /* alpha: difference b.t. original & modified .wav */
  vector<float> alpha;
  /* beta: machine interpretability with confidence */
  vector<float> beta;

  /* Evalueate fitness for each modified wav data */
  for (int i = 0; i < modified.size(); i++){
    /* alpha[i]: min(volume difference between original .wav and modified[i]) */
    float minVolumeDifference = -1;
    vector<uint8_t> modifiedData;
    modifiedData = modified.at(i).get();

    for (int j = 0; j < n; j++){
      string filename;
      /* original .wav file in original folder */
      filename = "../audio/original/original" + to_string(j) + ".wav";

      vector<uint8_t> originalData;
      originalData = Wav(filename).get();
      float VolumeDifference = 0;
      
      for (int k = 0; k < modified.size(); k++){
        VolumeDifference += abs(originalData.at(k) - modifiedData.at(k));
      }

      if (minVolumeDifference == -1){
        minVolumeDifference = VolumeDifference;
      }
      else{
        if (minVolumeDifference > VolumeDifference){
          minVolumeDifference = VolumeDifference;
        }
      }
    }
    alpha.push_back(minVolumeDifference);

    /* beta[i]: speechTotext interpretability of modified[i] */

    // beta.at(i) = interpretability(modified.at(i));
    beta.push_back(1);   //TODO
  }

  /* alpha normalization */
  float max_alpha = 0;
  for (int i = 0; i < modified.size(); i++){
    if (alpha.at(i) > max_alpha){
      max_alpha = alpha.at(i);
    }
  }
  
  // TODO

  // for (int i = 0; i < modified.size(); i++){
  //   alpha.at(i) /= max_alpha;
  // }
  
  /* Return result with combining alpha, beta by ratio argument */
  vector<float> result;
  for (int i = 0; i < modified.size(); i++){
    result.push_back(alpha.at(i) * ratio + beta.at(i) * (1 - ratio));
  }

  return result;
}