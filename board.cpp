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

#include "board.h"

/**
* Board constructor
*/
Board::Board(){

  // Seed random numbers
  init_rand();

  // Init the board
  init();  
}

void Board::init(){
  // Default values
  goal = DEFAULT_GOAL;
  score = 0;
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

  // Value color mappings
  valueColors = new int[5000];
  for(int i=0; i<5000; i++) valueColors[i] = -1;
  if(has_colors()){
    valueColors[64] = 1;
    valueColors[128] = 2;
    valueColors[256] = 3;
    valueColors[512] = 4;
    valueColors[1024] = 5;
    valueColors[2048] = 6;
  }

  // Random starting tiles
  for(int i=0; i<STARTING_TILE_COUNT; i++) addRandomTile();

  // Colors
  if(has_colors()){
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
  }
}

/* ============================================================ */
/* UTILITY                                                      */
/* ============================================================ */

/**
* Adds one random tile to the board, in a cell that's available if any is
*/
void Board::addRandomTile(){
  if(!isFull()){
    int x = getRand(0, MATRIX_SIZE-1);
    int y = getRand(0, MATRIX_SIZE-1);
    while(!isCellEmpty(x, y)){
      x = getRand(0, MATRIX_SIZE-1);
      y = getRand(0, MATRIX_SIZE-1);
    }
    int randTileIndex = getRand(0, countPossibleRandTiles-1);
    grid[x][y] = possibleRandTiles[randTileIndex];
  }
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

/**
* Indicates if the board is full
*/
bool Board::isFull(){
  int full = 0;
  for(int x=0; x<MATRIX_SIZE; x++){
    for(int y=0; y<MATRIX_SIZE; y++){
      full += !isCellEmpty(x, y) ? 1 : 0;
    }
  }
  return full >= MATRIX_SIZE*MATRIX_SIZE;
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
  printw("Press [X] to exit, [R] to restart the game.\n");
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

  // Score
  printw("Score: %d\n\n", score);

  // Board frame
  displayBoardHR();

  // Display it row by row (for this y, display all x...)
  for(int y=0; y<MATRIX_SIZE; y++){
    for(int x=0; x<MATRIX_SIZE; x++){
      int val = grid[x][y];
      if(val > 0){
        printw("|");
        if(valueColors[val] >= 0) attron(COLOR_PAIR(valueColors[val]));
        printw("%4d", val);
        if(valueColors[val] >= 0) attroff(COLOR_PAIR(valueColors[val]));
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

  if(isValidMoveKey(keyCode)){

    if(keyCode == 65 || keyCode == 'w'){
      if(moveUp()) addRandomTile();
    }else if(keyCode == 66 || keyCode == 's'){
      if(moveDown()) addRandomTile();
    }else if(keyCode == 67 || keyCode == 'd'){
      if(moveRight()) addRandomTile();
    }else if(keyCode == 68 || keyCode == 'a'){
      if(moveLeft()) addRandomTile();
    }
  }
}

/**
* Moves tiles up, indicates if a move was made
*/
bool Board::moveUp(){

  int moved = false;

  // Resolve the move column by column
  for(int x=0; x<MATRIX_SIZE; x++){
    for(int y=1; y<MATRIX_SIZE; y++){

      // as long as the cell above is empty, move it up
      int cy = y;
      while(isCellEmpty(x, cy-1) && cy > 0) cy--;

      if(
          cy > 0 && 
          !isCellEmpty(x,cy-1) && 
          getCell(x,y)==getCell(x,cy-1)
      ){
        int sum = getCell(x,y)+getCell(x,cy-1);
        setCell(x, cy-1, sum);
        setCellEmpty(x,y);
        score += sum;
        moved = true;
      }else if(cy != y){
        setCell(x, cy, getCell(x,y));
        setCellEmpty(x,y);
        moved = true;
      }
    }
  }

  return moved;
}

/**
* Moves tiles down, indicates if a move was made
*/
bool Board::moveDown(){
  int moved = false;

  // Resolve the move column by column
  for(int x=0; x<MATRIX_SIZE; x++){
    for(int y=MATRIX_SIZE-2; y>=0; y--){

      // as long as the cell above is empty, move it up
      int cy = y;
      while(isCellEmpty(x, cy+1) && cy < MATRIX_SIZE-1) cy++;

      if(
          cy < MATRIX_SIZE-1 && 
          !isCellEmpty(x,cy+1) && 
          getCell(x,y)==getCell(x,cy+1)
      ){
        int sum = getCell(x,y)+getCell(x,cy+1);
        setCell(x, cy+1, sum);
        setCellEmpty(x,y);
        score += sum;
        moved = true;
      }else if(cy != y){
        setCell(x, cy, getCell(x,y));
        setCellEmpty(x,y);
        moved = true;
      }
    }
  }

  return moved;
}

/**
* Moves tiles right, indicates if a move was made
*/
bool Board::moveRight(){
  int moved = false;

  // Resolve the move row by row
  for(int y=0; y<MATRIX_SIZE; y++){
    for(int x=MATRIX_SIZE-2; x>=0; x--){

      // as long as the cell above is empty, move it up
      int cx = x;
      while(isCellEmpty(cx+1, y) && cx < MATRIX_SIZE-1) cx++;

      if(
          cx < MATRIX_SIZE-1 && 
          !isCellEmpty(cx+1,y) && 
          getCell(x,y)==getCell(cx+1,y)
      ){
        int sum = getCell(x,y)+getCell(cx+1,y);
        setCell(cx+1, y, sum);
        setCellEmpty(x,y);
        score += sum;
        moved = true;
      }else if(cx != x){
        setCell(cx, y, getCell(x,y));
        setCellEmpty(x,y);
        moved = true;
      }
    }
  }

  return moved;
}

/**
* Moves tiles left, indicates if a move was made
*/
bool Board::moveLeft(){
  int moved = false;

  // Resolve the move row by row
  for(int y=0; y<MATRIX_SIZE; y++){
    for(int x=1; x<MATRIX_SIZE; x++){

      // as long as the cell above is empty, move it up
      int cx = x;
      while(isCellEmpty(cx-1, y) && cx > 0) cx--;

      if(
          cx > 0 && 
          !isCellEmpty(cx-1,y) && 
          getCell(x,y)==getCell(cx-1,y)
      ){
        int sum = getCell(x,y)+getCell(cx-1,y);
        setCell(cx-1, y, sum);
        setCellEmpty(x,y);
        score += sum;
        moved = true;
      }else if(cx != x){
        setCell(cx, y, getCell(x,y));
        setCellEmpty(x,y);
        moved = true;
      }
    }
  }

  return moved;
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
