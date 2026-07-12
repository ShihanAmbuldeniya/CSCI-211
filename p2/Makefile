# first target in a Makefile is the default target (memes in this file)
# this rule "makes" the final executable "memes"
memes: meme.o main.o
	g++ -Wall -pedantic -g -o memes meme.o main.o

# this rule "makes" main.o
# main.o depends on meme.h and main.cpp
main.o: meme.h main.cpp
	g++ -Wall -pedantic -g -std=c++11 -c main.cpp

# this rule "makes" meme.o
# meme.o depends on meme.h and meme.cpp
meme.o: meme.h meme.cpp
	g++ -Wall -pedantic -g -std=c++11 -c meme.cpp

clean:
	rm -f meme.o main.o memes memes.exe
