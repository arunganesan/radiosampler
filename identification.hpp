#include "audio.hpp"

class Identifier {
  int * matches;

protected:
  AudioManager * am;
  double calculateMatch (int, int) { return 0; }

public:
  Identifier (AudioManager *);
  void doAllMatches ();
};
