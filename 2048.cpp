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

#include "board.h"
#include "2048.h"

/**
* Main program
*/
int main(){

  // Initialize curses
  initscr();
  clear();
  cbreak();
  noecho();

  // Initialize board
  Board* b = new Board;
  b->display();

  // Key pressed
  int key = -1;

  while(!b->isGameFinished()){

    key = getch();

    // Wait for user to press valid key or 'x'
    while(!b->isValidMoveKey(key) && key!='x' && key!='r') key = getch();

    // User wants to exit
    if(key=='x') break;

    // User wants to restart
    if(key=='r'){
      delete b;
      b = new Board();
    }else{
      b->doMove(key);  // do the move
    }
    
    key = -1;        // reset key pressed

    // Refresh display
    clear();
    b->display();
  }

  // Clean-up curses
  endwin();
  
  return 0;
}


