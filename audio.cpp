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
General loading function.

This is used by the both the load Samples and load Groundtruth
*/
void AudioManager::loadFiles (string dirname, vector<Sample> &into) {
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
    
    sample.station = "";
    sample.offset = 0;
    sample.filename = filename;
    sample.audio = signal;
    sample.length = ff.frames();
    into.push_back(sample);
  }
}


/**
Loads the wave files from the directory.

Assumes the files are named in a particular format.

It extracts the offset, station name and everything needed.
*/
void AudioManager::loadSamples (string dirname) {
  loadFiles(dirname, samples);
  for (vector<Sample>::iterator it = samples.begin(); it != samples.end(); ++it) {
    string filename = it->filename;
    
    smatch what;
    sregex re = sregex::compile(".*/(\\d+)-\\w+-(\\d+\\.\\d).m4a.wav");
    regex_match(filename, what, re);
    it->station = what[2];
    double seconds_offset = stod(what[1])/1000;
    it->offset = int(seconds_offset*FS);
    cout << "Loaded " << it->filename << " station " << it->station << " offset " << it->offset << endl;
  }
}


/**
Loads the ground truth wave files.
Uses filename as the ground truth station.
The offset is set to 0 but is never used.
*/
void AudioManager::loadGroundTruth (string dirname) {
  loadFiles(dirname, groundTruth);
  for (vector<Sample>::iterator it = groundTruth.begin(); it != groundTruth.end(); ++it) {
    string filename = it->filename;
    
    smatch what;
    sregex re = sregex::compile(".*/(\\d+\\.\\d).wav");
    regex_match(filename, what, re);
    
    it->station = what[1];
    it->offset = 0;
    cout << "Loaded " << it->filename << " station " << it->station << " offset " << it->offset << endl;
  }
}


int AudioManager::evaluate (string matches []) { return 1; }

int AudioManager::getNumSamples () { return this->samples.size(); }
int AudioManager::getNumGroundTruth () { return this->groundTruth.size(); }

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
  
  cout << "Cropping ground truth " << gt.filename << " around sample " << sample.filename <<endl;
  
  int x0 = max(0, sample.offset - WINDOW);
  int x1 = min(gt.length-1, sample.offset + sample.length + WINDOW);
  
  // XXX: Who frees this memory?
  Sample * subset = new Sample(gt);
  subset->audio += x0;
  subset->length = x1 - x0;
  return *subset;
}















/**
 ____       _                       _             
 |  _ \  ___| |__  _   _  __ _  __ _(_)_ __   __ _ 
 | | | |/ _ \ '_ \| | | |/ _` |/ _` | | '_ \ / _` |
 | |_| |  __/ |_) | |_| | (_| | (_| | | | | | (_| |
 |____/ \___|_.__/ \__,_|\__, |\__, |_|_| |_|\__, |
                         |___/ |___/         |___/ 
*/

void AudioManager::saveSamples () {
  SF_INFO sfinfo;
  sfinfo.channels = 1;
  sfinfo.samplerate = FS;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
  
  for (vector<Sample>::iterator it = samples.begin(); it != samples.end(); ++it) {
    string file = "output/" + to_string(it->offset) + "-" + it->station + ".wav";
    cout << "Saving " << file << endl;
    SndfileHandle ofile = SndfileHandle(file, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, 1, 8000);
    ofile.write(it->audio, it->length);
    //sf_write_sync(ofile);
    //sf_close(ofile);
  }
}


void AudioManager::testCropping (int sId, int gId) {
  Sample cropped = getGroundTruthAround(sId, gId);
  SF_INFO sfinfo;
  sfinfo.channels = 1;
  sfinfo.samplerate = FS;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
  
  string file = "output/cropped.wav";
  cout << "Saving " << file << endl;
  SndfileHandle ofile = SndfileHandle(file, SFM_WRITE, SF_FORMAT_WAV | SF_FORMAT_PCM_16, 1, 8000);
  ofile.write(cropped.audio, cropped.length);

}

