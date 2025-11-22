#include <stdlib.h>
#include <stdio.h>
#include "../include/board.h"
#include "../include/board_print.h"

int main(void){
  Position pos;
  pos.x = 6;
  pos.y = 7;
  int width = 10;
  int height = 10;
  int mines = 67;
  Board board = board_create(width, height, mines, pos);
  printf("before fill\n");
  print_board(board);
  board_fill(board);
  printf("after fill\n");
  print_board(board);
}

