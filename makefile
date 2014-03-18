########################################
# Thomas Lextrait, thomas.lextrait@gmail.com
########################################
CC=gcc
CXX=g++
FLAGS=-c -Wall
CXXFLAGS=-c -Wall -Wextra -pedantic -Werror
########################################

# Make everything
all: 2048

# Make a fresh copy, clean up previous build
new: clean all

2048: 2048.o
		$(CXX) 2048.o -o 2048

2048.o: 2048.cpp 2048.h
		$(CXX) $(CXXFLAGS) 2048.cpp

########################################
# Clean up
########################################
clean:
		rm -f *.o *.out 2048
