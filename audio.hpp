#ifndef _AUDIO_INCL
#define _AUDIO_INCL

#include <sndfile.hh>
#include <vector>
using namespace std;
struct Sample {
  string station;
  string filename;
  int offset;
  double * audio;
  int length;
};


class AudioManager {
  vector<Sample> samples;
  vector<Sample> groundTruth;
  const int FS = 8000;
  const int WINDOW = 2*FS;

  void loadFiles (string, vector<Sample> &);

public:
  // Called by main to initialize audio manager 
  AudioManager();
  void loadSamples (string);
  void loadGroundTruth (string);
  int evaluate (int *);
  
  // Called by the individual algorithms 
  int getNumSamples ();
  int getNumGroundTruth ();
  Sample getSample (int);
  Sample getGroundTruthAround (int, int);


  // Debugging functions
  void saveSamples ();
  void testCropping (int, int);
  void plotSamples (vector<Sample> &) {}
};

#endif
