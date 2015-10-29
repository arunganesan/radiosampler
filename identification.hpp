#ifndef _IDENT_INCL
#define _IDENT_INCL

#include "audio.hpp"

class Identifier {
  int * matches;
  Identifier (Identifier &) {}
  Identifier () {}

protected:
  AudioManager * am;
  double calculateMatch (int, int) { return 0; }

public:
  Identifier (AudioManager *);
  void doAllMatches ();
  int * getMatches () { return matches; }
};


class XCorrIdentifier: public Identifier {
protected:
  double calculateMatch (int sid, int gid) {
    // We want to xcorr the SID with the GID
    // And return the sum or the max value
    return 0;
  }

public:
  XCorrIdentifier (AudioManager * am)  : Identifier (am) {}
};


class RandomIdentifier: public Identifier {
protected:
  double calculateMatch (int sid, int gid) { 
    srand(time(NULL));
    int guess = rand() % am->getNumGroundTruth();
    return guess;
  }
};
#endif
