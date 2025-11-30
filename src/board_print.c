#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/board.h"
#include "../include/board_print.h"

void tile_print(WINDOW * win, int y,int x,char c,int pair){
 // if ( has_colors()&& COLORS>=10&& COLOR_PAIRS)
 if (has_colors())
    wattron(win,COLOR_PAIR(pair));

  mvwaddch(win,y,x,c);

 if (has_colors()) 
    wattroff(win,COLOR_PAIR(pair)); 
}
void print_board(Board board, WINDOW* board_win) {
  //dealing with colors, 0 will be the "base color" of white, 1-8 will be the colors for the numbers 9 will be for flags and 10 for mines
    //                  base           1         2           3         4         5          6            7            8        flag      bombs 
  int colorboard[]={COLOR_WHITE,COLOR_BLUE,COLOR_GREEN,COLOR_RED,COLOR_BLUE,COLOR_RED,COLOR_CYAN,COLOR_MAGENTA,COLOR_WHITE,COLOR_RED,COLOR_BLACK};
  if(has_colors()){
    start_color();
    refresh();

    //making the color pairs 
    for (int i=0;i<10;i++){
      init_pair(i,colorboard[i],COLOR_BLACK);
      
    }
    //making bomb's pair seperately so that it can have a red bakcground
    init_pair(10,colorboard[10],COLOR_RED);
  }
  int char_offset='0';
  char not_cleared= '#';
  int tile_value=0;
  char empty=' ';
  char bomb = 'X';
  char flag = 'F';
  for (int x = 1; x <= board.width; x++) {
    for (int y = 1; y <= board.height; y++) {

      if (board.tiles[x-1][y-1].flag)
        tile_print(board_win,y,x,flag,9);

      else if (!board.tiles[x-1][y-1].cleared)
        tile_print(board_win,y,x,not_cleared,0);
      else{
        tile_value=board.tiles[x-1][y-1].value;
        tile_print(board_win,y,x,char_offset+tile_value,tile_value);
        if (tile_value==0) tile_print(board_win,y,x,empty,0);
      }  
      if (board.tiles[x-1][y-1].type==MINE&&*board.lost)
        tile_print(board_win,y,x,bomb,10);
    } 
  }
  //printing numbers on the boarder 
  box (board_win,0,0);
  mvwprintw(board_win,0,1,"%d",(board.mines)-(*board.flags));
  //printing seed
  mvwprintw(board_win,board.height+1,1,"s:%x",board.seed);
  wrefresh(board_win); 
}

void print_command_list() {
  printf("Command list:\n"); 
  printf("c x_coordinate y_coordinate : clear tile on position(x_coordinate, y_coordinate)\n");
  printf("f x_coordinate y_coordinate : flag tile on position(x_coordinate y_coordinate)\n");
  printf("u x_coordinate y_coordinate : unflag tile on position(x_coordinate y_coordinate)\n");
  return;
}

