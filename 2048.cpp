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

  // generate secret number between 1 and 10
  //int iSecret = rand() % 10 + 1;

  Screen* sc;
  sc = new Screen();

  Board* b = new Board;
  b->display();

  //printw("Press F1\n");
  //getch();
  //printw("%d\n", CH);

  delete sc;
  
  return 0;
}


