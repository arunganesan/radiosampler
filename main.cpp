#include <iostream>
#include <sndfile.hh>
#include <boost/filesystem.hpp>

#include "audio.hpp"

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
  AudioManager am;
  am.loadSamples("sampled-repos/car-clean-10.26.2015/");
  am.loadGroundTruth("audio-repos/car-clean-10.26.2015/");
  return 0;
}
