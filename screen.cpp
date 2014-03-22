/**
 * screen.cpp
 *
 * Thomas Lextrait
 * thomas.lextrait@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h> // for getch(), keyboard events

#include "screen.h"

/**
* Screen constructor
*/
Screen::Screen(){
  //initialized = false;
  //destroyed = false;
  
  printf("HELLO WORLD");


  //initialize();
}

/**
* Screen destructor
*/
Screen::~Screen(){
  destroy();
}

/**
* Initialize the screen object (private)
*/
void Screen::initialize(){
  if(!initialized){
    printf("HELLO\n");
    //initscr();  // init the screen with curses
    printf("1\n");
    //clear();
    printf("2\n");
    noecho();   // don't echo inputs
    cbreak();
    printf("5\n");
    initialized = true;
  }
}

/**
* Destroy and cleanup the screen object
*/
void Screen::destroy(){
  if(!destroyed){
    endwin();
    destroyed = true;
  }
}

/**
* Clear screen (static)
*/
void Screen::clear(){
  //ncurses function to clear screen
  clear();
}

void init_curses(){
  initscr();
  clear();
  cbreak();
  noecho();
  getch();
}

void end_curses(){
  endwin();
}
