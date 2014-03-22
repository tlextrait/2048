/**
 * 2048.cpp
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
#include "2048.h"

/**
* Constructor
*/
Board::Board(){

  // Default values
  goal = 2048;

  // Initialize grid
  for(int i=0; i<MATRIX_SIZE; i++){
    for(int j=0; j<MATRIX_SIZE; j++){
      grid[i][j] = 0;
    }
  }
}

/**
* Displays the board
*/
void Board::display(){
  for(int x=0; x<MATRIX_SIZE; x++){
    for(int y=0; y<MATRIX_SIZE; y++){
      int val = grid[x][y];
      if(val > 0){
        printw("[%d]", val);
      }else{
        printw("[ ]");
      }
    }
    printw("\n");
  }
  printw("\n");
}

/**
* Main program
*/
int main(){

  // initialize random seed
  srand(time(NULL));

  // generate secret number between 1 and 10
  //int iSecret = rand() % 10 + 1;

  Screen* sc;
  sc = new Screen();

  //Board* b = new Board;
  //b->display();

  //printw("Press F1\n");
  //getch();
  //printw("%d\n", CH);

  delete sc;
  
  return 0;
}


