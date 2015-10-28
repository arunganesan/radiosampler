#include <iostream>
#include <sndfile.hh>
#include <boost/filesystem.hpp>

#include "audio.hpp"
#include "identification.hpp"

using namespace std;
using namespace boost::filesystem;


void list_all_files () {
  path p(".");
  directory_iterator end_itr;
  for (directory_iterator itr(p); itr != end_itr; ++itr) {
    if (is_regular_file(itr->path())) {
      string current_file = itr->path().string();
      cout << current_file << endl;
    }
  }
}


int main () {
  AudioManager * am = new AudioManager();
  am->loadSamples("sampled-repos/car-clean-10.26.2015/");
  am->loadGroundTruth("audio-repos/car-clean-10.26.2015/");
  Identifier id = Identifier(am);
  //Identifier identifiers [2] = {XCorrIdentifier(am), RandomIdentifier(am)};
  return 0;
}
