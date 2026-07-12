# Makefile for 211 p3 assignment
mlist: meme.o main.o mlist.o
	g++ -Wall -pedantic -g -o mlist meme.o main.o mlist.o

# main.cpp includes meme.h and mlist.h
main.o: main.cpp meme.h mlist.h
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp

# meme.cpp includes meme.h
meme.o: meme.h meme.cpp
	g++ -Wall -pedantic -g -std=c++11 -c meme.cpp

# mlist.cpp includes mlist.h and meme.h
mlist.o: mlist.h mlist.cpp meme.h
	g++ -Wall -pedantic -g -std=c++11 -c mlist.cpp

# these are the files created from the above commands
clean:
	rm -f meme.o main.o mlist.o mlist mlist.exe
