CC = g++

default: audio.o utils.o
	$(CC) main.cpp -std=gnu++11 -o main utils.o audio.o -lsndfile -lboost_system -lboost_filesystem

all: clean default

audio.o: utils.o
	$(CC) -c -std=gnu++11 audio.cpp -o audio.o utils.o -lsndfile -lboost_system -lboost_filesystem

utils.o:
	$(CC) -c -std=gnu++11 utils.cpp -o utils.o -lboost_system -lboost_filesystem

clean:
	rm *.o
