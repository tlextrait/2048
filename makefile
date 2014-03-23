########################################
# Thomas Lextrait, thomas.lextrait@gmail.com
########################################
CC=gcc
CXX=g++
FLAGS=-c -Wall
CXXFLAGS=-c -Wall -Wextra -pedantic -Werror
LIBFLAGS = -lncurses
########################################

# Make everything
all: 2048

# Make a fresh copy, clean up previous build
new: clean all

2048: 2048.o board.o
		$(CXX) 2048.o board.o -o 2048 $(LIBFLAGS)

2048.o: 2048.cpp 2048.h board.h
		$(CXX) $(CXXFLAGS) 2048.cpp board.cpp

board.o: board.cpp board.h
		$(CXX) $(CXXFLAGS) board.cpp

########################################
# Clean up
########################################
clean:
		rm -f *.o *.out 2048
