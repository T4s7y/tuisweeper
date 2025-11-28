#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/board.h"
#include "../include/board_print.h"

void print_board(Board board, WINDOW* board_win) {
  char empty = '#';
  char bomb = 'X';
  char flag = 'F';
  for (int x = 1; x <= board.width; x++) {
    for (int y = 1; y <= board.height; y++) {
      if (board.tiles[x-1][y-1].flag)
        mvwprintw(board_win, y, x, "%c", flag);   
      else if (!board.tiles[x-1][y-1].cleared)
        mvwprintw(board_win, y, x, "%c", empty);
      else
        mvwprintw(board_win, y, x, "%d", board.tiles[x-1][y-1].value);
      } 
  }
  wrefresh(board_win); 
}

void print_command_list() {
  printf("Command list:\n"); 
  printf("c x_coordinate y_coordinate : clear tile on position(x_coordinate, y_coordinate)\n");
  printf("f x_coordinate y_coordinate : flag tile on position(x_coordinate y_coordinate)\n");
  printf("u x_coordinate y_coordinate : unflag tile on position(x_coordinate y_coordinate)\n");
  return;
}

