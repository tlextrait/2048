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

2048: 2048.o screen.o board.o
		$(CXX) 2048.o board.o screen.o -o 2048 $(LIBFLAGS)

2048.o: 2048.cpp 2048.h board.h screen.h
		$(CXX) $(CXXFLAGS) 2048.cpp board.cpp screen.cpp

board.o: board.cpp board.h screen.h
		$(CXX) $(CXXFLAGS) board.cpp

screen.o: screen.cpp screen.h
		$(CXX) $(CXXFLAGS) screen.cpp

########################################
# Clean up
########################################
clean:
		rm -f *.o *.out 2048
