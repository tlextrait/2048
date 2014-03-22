/**
 * 2048.cpp
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h> // for getch(), keyboard events

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

  initscr();
  clear();
  noecho();
  cbreak();

  Board* b = new Board;
  b->display();
  
  printw("Press F1\n");
  int CH = getch();
  printw("%d\n", CH);

  getch();
  endwin();

  /* Initialize curses */

  
  return 0;
}
