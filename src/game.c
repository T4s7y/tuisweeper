#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "../include/board.h"
#include "../include/board_print.h"
#include "../include/commands.h"

#define MAX_WIDTH 100
#define MAX_HEIGHT 100

char* difficulties[] = {"beginner", "intermediate", "expert"};

// User enters width, height and number of mines 
int main(int argc, char* argv[]) {
  srand(time(NULL));
  if (argc != 2 && argc != 4) {
    printf("usage: \n %s [difficulty] \n valid difficulties are: beginner,intermediate,expert\n%s [width] [height] [mines]\n",argv[0],argv[0]);
    return 1;
  }
 int width,height,mines; 
  if (argc==2){
      if(strcmp(argv[1],difficulties[0])==0){
        width=10;
        height=10;
        mines=9;
      }
      else if(strcmp(argv[1],difficulties[1])==0){
        width=16;
        height=16;
        mines=40;
      }
      else if (strcmp(argv[1],difficulties[2])==0){
        width=30;
        height=16;
        mines=99;
      }
      else {
      printf("invalid difficulty \n");
      return 1; 
      }
    
    }

  else {
    width = atoi(argv[1]);
    if (width <= 0 || width >= MAX_WIDTH) {
      printf("Invalid width\n");
      return 1;
    }

    height = atoi(argv[2]);
    if (height <= 0 || height >= MAX_HEIGHT) {
      printf("Invalid height\n");
      return 1;
    }

    mines = atoi(argv[3]);
    if (mines <= 0 || mines >= width*height) {
      printf("Invalid amount of mines\n");
      return 1;
    }
  }


  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  // Window initialisation
  int x_max, y_max;
  getmaxyx(stdscr, y_max, x_max);
  int x_offset = x_max/2-(width/2+1);
  int y_offset = y_max/2-(height/2+1);
  // Window should be centered
  WINDOW * board_win = newwin(height+2, width+2, y_offset, x_offset);
  box(board_win, 0, 0);
  refresh();
  wrefresh(board_win);
  
  // Mouse input 
  mousemask(ALL_MOUSE_EVENTS, NULL);
  MEVENT mouse;
  int ch;
  keypad(board_win, TRUE);

  // Board initialisation
  Board board = board_create(width, height, mines);
  print_board(board, board_win);
  Position pos;
  bool first_round = true;

  refresh();
  while(1) {
    ch = wgetch(board_win);
    if (ch != KEY_MOUSE)
     continue; 
    else
      if (getmouse(&mouse) == OK) {
        pos.x = mouse.x-x_offset;
        pos.y = mouse.y-y_offset;
      }
      else continue;
    if (!check_command(mouse.bstate, board, pos))
      continue;

    if (first_round) {
      if (mouse.bstate == BUTTON1_CLICKED) {
        pos.x--;
        pos.y--;
        board.first_pos = pos;
        pos.x++;
        pos.y++;
      }
      board_fill(board);
      first_round = false;
    }
    
    command_translator(mouse.bstate, board, pos);
    print_board(board, board_win);
   if (*board.lost){
      mvprintw(y_offset,x_offset,"YOU LOSE");
      break;
   }
   if((*board.cleared_tiles+mines)== (height*width)){
      mvprintw(y_offset,x_offset,"YOU WIN");
      break;
    }
    wrefresh(board_win);
    
  }
  

  board_destroy(board);
  getch();
  endwin();
  return 0;
}
