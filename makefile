########################################
# Thomas Lextrait, thomas.lextrait@gmail.com
########################################
CC=g++
FLAGS=-c -Wall
########################################

# Make everything
all: 2048

# Make a fresh copy, clean up previous build
new: clean all

2048: 2048.o
		$(CC) 2048.o -o 2048

2048.o: 2048.cpp 2048.h
		$(CC) $(FLAGS) 2048.cpp

########################################
# Clean up
########################################
clean:
		rm -f *.o *.out 2048
