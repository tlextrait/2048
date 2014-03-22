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
  maxTile = 0;

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

/* ============================================================ */
/* UTILITY                                                      */
/* ============================================================ */

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

bool Board::isValidCoordinates(int x, int y){
  return x >=0 && x < MATRIX_SIZE && y >= 0 && y < MATRIX_SIZE;
}

/**
* Returns the value of a cell
*/
int Board::getCell(int x, int y){
  return isValidCoordinates(x, y) ? grid[x][y] : -1;
}

/**
* Indicates if the given cell is empty
*/
bool Board::isCellEmpty(int x, int y){
  return !isValidCoordinates(x, y) || grid[x][y] <= 0;
}

/**
* Sets the value of given cell
*/
void Board::setCell(int x, int y, int val){
  if(isValidCoordinates(x, y)){
    grid[x][y] = val;
  }
}

/**
* Sets the given cell as empty
*/
void Board::setCellEmpty(int x, int y){
  setCell(x, y, 0);
}

/* ============================================================ */
/* DISPLAY                                                      */
/* ============================================================ */

void Board::displayHeaderHR(){
  printw("=======================================================\n");
}

void Board::displayHeader(){
  printw("\n");
  printw("2048 - Implemented in C++ by Thomas Lextrait\n");
  displayHeaderHR();
  printw("\n");
}

void Board::displayFooter(){
  displayHeaderHR();
  printw("Use the arrows or the [W][A][S][D] keys to shift tiles on the board.\n");
  printw("Press [X] to exit.\n");
}

void Board::displayBoardHR(){
  for(int i=0; i<MATRIX_SIZE; i++){
    printw("+");
    for(int a=0; a<CELL_SIZE; a++){
      printw("-");
    }
  }
  printw("+\n");
}

void Board::displayBoard(){
  displayBoardHR();
  for(int x=0; x<MATRIX_SIZE; x++){
    for(int y=0; y<MATRIX_SIZE; y++){
      int val = grid[x][y];
      if(val > 0){
        printw("|%4d", val);
      }else{
        printw("|    ");
      }
    }
    printw("|\n");
    displayBoardHR();
  }
  printw("\n"); // end with new line
}

/**
* Displays the board
*/
void Board::display(){
  displayHeader();
  displayBoard();
  displayFooter();
}

/* ============================================================ */
/* MOVES                                                        */
/* ============================================================ */

bool Board::isValidMoveKey(int keyCode){
  return 
    keyCode == 65 || // up
    keyCode == 66 || // down
    keyCode == 67 || // right
    keyCode == 68 || // left
    keyCode == 'a' || 
    keyCode == 'w' || 
    keyCode == 's' || 
    keyCode == 'd';
}

void Board::doMove(int keyCode){

  if(keyCode == 65 || keyCode == 'w'){
    moveUp();
  }else if(keyCode == 66 || keyCode == 's'){
    moveDown();
  }else if(keyCode == 67 || keyCode == 'd'){
    moveRight();
  }else if(keyCode == 68 || keyCode == 'a'){
    moveLeft();
  }

  if(isValidMoveKey(keyCode)) addRandomTile();
}

/*

0 0 0 0
0 0 0 0
0 0 0 0
0 0 0 0

*/

void Board::moveUp(){
  printw("MOVING UP");
  // Resolve the move column by column
  for(int x=0; x<MATRIX_SIZE; x++){
    for(int y=0; y<MATRIX_SIZE-1; y++){
      printw(".");
      if(isCellEmpty(x, y)){
        // move up cell from below
        setCell(x, y, getCell(x, y+1));
      }else{
        if(getCell(x,y) == getCell(x,y+1)){
          setCell(x, y, (getCell(x,y) + getCell(x,y+1)));
        }
      }
    }
  }
}

void Board::moveRight(){

}

void Board::moveDown(){

}

void Board::moveLeft(){

}

/* ============================================================ */
/* STATE                                                        */
/* ============================================================ */

bool Board::isGameFinished(){
  return isGameWon() || isGameOver();
}

bool Board::isGameWon(){
  return maxTile >= goal;
}

bool Board::isGameOver(){
  /*
  @TODO
  */
  return false;
}

/* ============================================================ */
/* MISC                                                         */
/* ============================================================ */

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
