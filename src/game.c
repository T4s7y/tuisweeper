#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "../include/board.h"
#include "../include/board_print.h"
#include "../include/commands.h"

// Base difficulties
char* difficulties[] = {"beginner", "intermediate", "expert"};

// User enters width, height and number of mines 
int main(int argc, char* argv[]) {
  //setting the seed to current time, this will be overwritten if the user inputs their own seed 
  int seed=time(NULL);
  if (argc!=2 && argc != 3 && argc != 4 && argc!=5) {
    printf("usage: \n %s [difficulty] \n valid difficulties are: beginner,intermediate,expert\n%s [width] [height] [mines]\n optionally after a valid input you can enter a seed to revisit a board \n",argv[0],argv[0]);
    return 1;
  }
  int width,height,mines; 

  // Starting screen calls
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);

  // Getting terminal dimensions 
  int x_max, y_max;
  getmaxyx(stdscr, y_max, x_max);

  // Checking for valid inputs 
  if (argc==2||argc==3){
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
      endwin();
      printf("invalid difficulty \n");
      return 1; 
      }
      if (argc==3){

      seed=(int)strtol(argv[2],NULL,16);

      }
    }

  else {
    width = atoi(argv[1]);
    if (width <= 0 || width >= x_max) {
      endwin();
      printf("invalid width, max width = %d\n",x_max-2);
      return 1;
    }

    height = atoi(argv[2]);
    if (height <= 0 || height >= y_max) {
      endwin();
      printf("invalid height, max height= %d\n",y_max-2);
      return 1;
    }

    mines = atoi(argv[3]);
    if (mines <= 0 || mines >= width*height) {
      endwin();
      printf("Invalid amount of mines, can't have more than (height*width)-1\n");
      return 1;
    }
    if (argc==5){
      seed=(int)strtol(argv[4],NULL,16);
    }
  }

  // Window should be centered  
  int x_offset = x_max/2-(width/2+1);
  int y_offset = y_max/2-(height/2+1);

  // Window initialisation 
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
  Board board = board_create(width, height, mines,seed);
  //setting the seed
  print_board(board, board_win);
  Position pos;
  bool first_round = true;
  refresh();

  // Game loop
  while(1) {
    //getting board dimensions
    getmaxyx(stdscr, y_max, x_max);
    //checking if we need to resize the board
    if (y_offset != y_max/2-(height/2+1)|| x_offset != x_max/2-(width/2+1)){
      y_offset= y_max/2-(height/2+1);
      x_offset= x_max/2-(width/2+1);

      mvwin(board_win,y_offset,x_offset);
      clear();
      refresh();
      wrefresh(board_win);
    }
    else {
      ch = wgetch(board_win);
    }

    if ((ch == KEY_MOUSE) && (getmouse(&mouse) == OK))
      pos = (Position){mouse.x-x_offset, mouse.y-y_offset};
    else
     continue; 

    if (!check_command(mouse.bstate, board, pos))
      continue;

    if (first_round) {
      if (mouse.bstate == BUTTON1_CLICKED) 
        board.first_pos = (Position){pos.x-1, pos.y-1};
      board_fill(board);
      first_round = false;
    }
    
    command_translator(mouse.bstate, board, pos);
    print_board(board, board_win);

    // Lose condition
    if (*board.lost){
      mvprintw(y_offset,x_offset,"YOU LOSE");
      break;
    }
    // Win condition
    if((*board.cleared_tiles+mines)== (height*width)){
      mvprintw(y_offset,x_offset,"YOU WIN");
      break;
    }
    wrefresh(board_win);
  }
  
  // Clean up
  board_destroy(board);
  getch();
  endwin();
  return 0;
}
