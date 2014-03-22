/**
 * board.cpp
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for random numbers
#include <curses.h> // for getch(), keyboard events

#include "screen.h"
#include "board.h"

/**
* Board constructor
*/
Board::Board(){

  // Seed random numbers
  init_rand();

  // Default values
  goal = DEFAULT_GOAL;

  // Initialize grid
  for(int i=0; i<MATRIX_SIZE; i++){
    for(int j=0; j<MATRIX_SIZE; j++){
      grid[i][j] = 0;
    }
  }

  // Possible random tiles
  possibleRandTiles = new int[2];
  possibleRandTiles[0] = 2;
  possibleRandTiles[1] = 4;
  countPossibleRandTiles = 2;

  // Random starting tiles
  for(int i=0; i<STARTING_TILE_COUNT; i++) addRandomTile();
}

/**
* Adds one random tile to the board, in a cell that's available if any is
*/
void Board::addRandomTile(){
  int x = getRand(0, MATRIX_SIZE-1);
  int y = getRand(0, MATRIX_SIZE-1);
  while(!isCellEmpty(x, y)){
    x = getRand(0, MATRIX_SIZE-1);
    y = getRand(0, MATRIX_SIZE-1);
  }
  int randTileIndex = getRand(0, countPossibleRandTiles-1);
  grid[x][y] = possibleRandTiles[randTileIndex];
}

/**
* Indicates if the given cell is empty
*/
bool Board::isCellEmpty(int x, int y){
  return grid[x][y] <= 0;
}

/**
* Displays the board
*/
void Board::display(){
  for(int x=0; x<MATRIX_SIZE; x++){
    for(int y=0; y<MATRIX_SIZE; y++){
      int val = grid[x][y];
      if(val > 0){
        printw("[%4d]", val);
      }else{
        printw("[    ]");
      }
    }
    printw("\n");
  }
  printw("\n");
}

/**
* Initializes and seeds the number generator
*/
void init_rand(){
  srand(time(NULL));
}

/**
* Generates a random number between min and max (both inclusive)
*/
int getRand(int min, int max){
  return rand() % (max+1) + min;
}
