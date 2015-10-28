CC = g++

default: audio.o utils.o identification.o
	$(CC) main.cpp -std=gnu++11 -o main utils.o audio.o identification.o -lsndfile -lboost_system -lboost_filesystem

all: clean default

audio.o: utils.o
	$(CC) -c -std=gnu++11 audio.cpp -o audio.o utils.o -lsndfile -lboost_system -lboost_filesystem

utils.o:
	$(CC) -c -std=gnu++11 utils.cpp -o utils.o -lboost_system -lboost_filesystem


identification.o:
	$(CC) -c -std=gnu++11 identification.cpp -o identification.o

clean:
	rm *.o
