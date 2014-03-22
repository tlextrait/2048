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

  Screen* sc;
  sc = new Screen();

  Board* b = new Board;
  b->display();

  int ch = 0;

  while(!b->isGameFinished()){
    while(!b->isValidMoveKey(ch)) ch = getch();
    b->doMove(ch);
  }

  // Clean-up!
  delete sc;
  
  return 0;
}


