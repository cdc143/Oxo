#include <ncurses.h>
#include <stdio.h>
#include "game.h"
#include <locale.h>
#include <libintl.h>
#include <stdlib.h>

void cursesinit() {
  //Initialize curses with various options. See curses documentation for how the work
  initscr();
  cbreak();
  noecho();
  keypad(stdscr,TRUE);
}

int main () {
  setlocale ( LC_ALL, "" );
  bindtextdomain("game", getenv("PWD"));
  textdomain("game");
  cursesinit(); //init curses
  drawBoard(); //draw the game board
  gameLoop(); //do game loop
  endwin(); //clean everything up and exit
  return 0;
}
