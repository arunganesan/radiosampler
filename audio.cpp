#include "audio.hpp"
#include "utils.hpp"

#include <sndfile.hh>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

AudioManager::AudioManager () {}

void AudioManager::loadSamples (string dirname) {
  vector<string> filenames = list_all_files(dirname); 
  for (vector<string>::iterator it = filenames.begin(); it != filenames.end(); ++it) {
    string filename = *it;
    if (filename.find(".wav") == string::npos) continue;
    
    Sample sample;
    SndfileHandle ff = SndfileHandle(filename);
    double * signal = new double [ff.frames()];
    ff.read(signal, ff.frames());
    
    smatch sm;
    try {
      //regex r(".*/(\d+)-\w+-(\d+.\d).m4a.wav");
      regex r(".*(\d+).*");
      regex_match(filename, sm, r);
      cout << "sm size is " << sm.size() << endl;
      for (unsigned i = 0; i < sm.size(); ++i) {
        cout << "[" << sm[i].str() << "]";
      }
    } catch (regex_error e) {
      cout << "Error" << endl;
      cout << e.what() << endl;
      cout << "CODE IS " << e.code() << endl;
    
      cout << "collate: " << regex_constants::error_collate << endl;
      cout << "caollate: " << regex_constants::error_brack << endl;
    }
    
    sample.filename = filename;
    sample.audio = signal;
    sample.length = ff.frames();
    this->samples.push_back(sample);
    cout << "Loaded " << sample.filename << endl;
  }
}


void AudioManager::loadGroundTruth (string dirname) {}
int AudioManager::evaluate (string matches []) { return 1; }

int AudioManager::getNumSamples () { 
  return this->samples.size();  
}

int AudioManager::getNumGroundTruth () {
  return this->groundTruth.size();
}

Sample AudioManager::getSample (int id) {
  return Sample();
}

Sample AudioManager::getGroundTruthAround (int sampleId, int gtId) {
  return Sample();
}
