#include "identification.hpp"
#include "audio.hpp"

#include <stdlib.h>
#include <time.h>

Identifier::Identifier (AudioManager * otherAm) {
  am = otherAm;
  matches = new int [am->getNumSamples()];
}

/**
This function is called by the main class for each identifier.
The identifier then updates an internal map of each match
The internal match can then be used to calculate the accuracy
*/
void Identifier::doAllMatches () {
  int samples = am->getNumSamples();
  int gtsamples = am->getNumGroundTruth();
  
  // For each sample, find the best match
  // Then update the internal array of ints
  
  for (int si = 0; si < samples; si++) {
    // TODO: Multithread this part.

    double best_score = -1;
    double best_gi = 0;
    double score;
    for (int gi = 0; gi < gtsamples; gi++) {
      score = calculateMatch(si, gi);
      if (score > best_score) {
        best_score = score;
        best_gi = gi;
      }
    }
    
    this->matches[si] = best_gi;
  }
}






