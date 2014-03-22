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
  initialized = false;
  destroyed = false;
  initialize();
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
    init_curses();
    initialized = true;
  }
}

/**
* Destroy and cleanup the screen object
*/
void Screen::destroy(){
  if(!destroyed){
    end_curses();
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

/**
* Initialize curses
*/
void init_curses(){
  initscr();
  clear();
  cbreak();
  noecho();
}

/**
* Clean up curses
*/
void end_curses(){
  endwin();
}
