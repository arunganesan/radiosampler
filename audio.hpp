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
  int evaluate (string []);
  
  // Called by the individual algorithms 
  int getNumSamples ();
  int getNumGroundTruth ();
  Sample getSample (int);
  Sample getGroundTruthAround (int, int);
};
