This set of C++ programs are used to evaluate various audio identification 
algorithms to identify the radio station. Amongst others, it will be used to 
evaluate *Shazam fingerprinting*, *Cross Correlation*, and *Relative Matching*.
It is concerned with various metrics such as how accurately each algorithm 
identifies the station, how much noise it can withstand, how quickly it can 
identify, etc. This set of programs can be used to answer questions about the 
cloud-based identification, local locking and local scanning algorithms.

# ~~Supported~~ Planned matching functions
For each of these functions, we will use the same wrapper code which evaluates
some metrics on each of them. Also, for each system, the algorithm either takes
a full recording and crops out the portion based on time syncing.

## Shazam-style fingerprinting
*Parameters*
- Fan out size
- Window size of each time sample
- Some threshold for detecting peak in spectrogram
- This takes as input the ground truth file and samples

*Operation*
- Takes the spectrogram of the audio sample
- Finds prominent peaks
- Then looks for other peaks in the fan-out region
- Takes the peak location and offset to create hash
- Matches based on alignment of fingerprints in sample and ground truth

*Variants*
- Just based on count
- Fully based on alignment

## Cross correlation

## Relative Matching
- Top secret.

# Candidate libraries
- [libsndfile](http://www.mega-nerd.com/libsndfile/)
- [Alglib](http://www.alglib.net/)
- STL
- [Boost](http://www.boost.org/)
- [uBLAS](http://www.boost.org/doc/libs/1_59_0/libs/numeric/ublas/doc/)
