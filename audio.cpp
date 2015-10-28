#include "audio.hpp"
#include "utils.hpp"

#include <sndfile.hh>
#include <iostream>
#include <string>
#include <boost/xpressive/xpressive.hpp>


using namespace std;
using namespace boost;
using namespace xpressive;


AudioManager::AudioManager () {}

/**
Loads the wave files from the directory.

Assumes the files are named in a particular format.

It extracts the offset, station name and everything needed.
*/
void AudioManager::loadSamples (string dirname) {
  vector<string> filenames = list_all_files(dirname); 
  for (vector<string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
    string filename = *it;
    if (filename.find(".wav") == string::npos) continue;
    
    Sample sample;
    SndfileHandle ff = SndfileHandle(filename);
    assert(ff.channels() == 1);
    assert(ff.samplerate() == 8000);
    double * signal = new double [ff.frames()];
    ff.read(signal, ff.frames());
    
    smatch what;
    sregex re = sregex::compile(".*/(\\d+)-\\w+-(\\d+\\.\\d).m4a.wav");
    regex_match(filename, what, re);
    
    sample.station = what[2];
    sample.offset = stoi(what[1]);
    sample.filename = filename;
    sample.audio = signal;
    sample.length = ff.frames();
    this->samples.push_back(sample);
    cout << "Loaded " << sample.filename << " station " << sample.station << " offset " << sample.offset << endl;
  }
}


/**
Loads the ground truth wave files.
Uses filename as the ground truth station.
The offset is set to 0 but is never used.
*/
void AudioManager::loadGroundTruth (string dirname) {
  vector<string> filenames = list_all_files(dirname); 
  for (vector<string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
    string filename = *it;
    if (filename.find(".wav") == string::npos) continue;
    
    Sample sample;
    SndfileHandle ff = SndfileHandle(filename);
    assert(ff.channels() == 1);
    assert(ff.samplerate() == 8000);
    double * signal = new double [ff.frames()];
    ff.read(signal, ff.frames());
    
    smatch what;
    sregex re = sregex::compile(".*/(\\d+\\.\\d).wav");
    regex_match(filename, what, re);
    
    sample.station = what[1];
    sample.offset = 0;
    sample.filename = filename;
    sample.audio = signal;
    sample.length = ff.frames();
    this->samples.push_back(sample);
    cout << "Loaded " << sample.filename << " station " << sample.station << " offset " << sample.offset << endl;
  }
}


int AudioManager::evaluate (string matches []) { return 1; }

int AudioManager::getNumSamples () { 
  return this->samples.size();  
}

int AudioManager::getNumGroundTruth () {
  return this->groundTruth.size();
}

Sample AudioManager::getSample (int id) {
  assert (id < this->samples.size());
  return this->samples.at(id);
}



/**
Makes a new sample and simply offsets the pointer 

The length is adjusted based on new cropped size

Assumes the subset is not directly modified by anyone.
*/

Sample AudioManager::getGroundTruthAround (int sampleId, int gtId) {
  assert (sampleId < this->samples.size());
  assert (gtId < this->groundTruth.size());

  Sample sample = this->samples[sampleId];
  Sample gt = this->groundTruth[gtId];

  int x0 = max(0, sample.offset - WINDOW);
  int x1 = min(gt.length-1, sample.offset + sample.length + WINDOW);

  Sample * subset = new Sample(gt);
  subset->audio += x0;
  subset->length = x1 - x0;
  return *subset;
}
