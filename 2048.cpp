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

#include "screen.h"
#include "board.h"
#include "2048.h"

/**
* Main program
*/
int main(){

  initscr();
  clear();
  cbreak();
  noecho();

  Board* b = new Board;
  b->display();

  int ch = -1;

  while(!b->isGameFinished()){

    printw("Make a move...\n");

    while(!b->isValidMoveKey(ch) && ch!='x') ch = getch();

    // User wants to exit
    if(ch=='x') break;

    b->doMove(ch);  // do the move
    ch = -1;        // reset key pressed

    // Refresh display
    clear();
    b->display();
  }

  // Clean-up curses
  endwin();
  
  return 0;
}


