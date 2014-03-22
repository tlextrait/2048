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

  //printw("Press F1\n");
  //getch();
  //printw("%d\n", CH);

  getch();

  delete sc;
  
  return 0;
}


