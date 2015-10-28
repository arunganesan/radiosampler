#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;


vector<string> list_all_files (string dirname) {
  vector<string> files;

  path p (dirname);
  directory_iterator end_itr;
  for (directory_iterator itr(p); itr != end_itr; ++itr) {
    if (is_regular_file(itr->path())) {
      string current_file = itr->path().string();
      files.push_back(current_file);    
    }
  }

  return files;
}





