#include <stdlib.h>
#include <stdio.h>
#include "../include/board.h"
#include "../include/board_print.h"

int main(void){
  Position pos;
  pos.x = 2;
  pos.y = 2;
  int width = 20;
  int height = 9;
  int mines = 10;
  Board board = board_create(width, height, mines, pos);
  printf("before fill\n");
  print_board(board, width, height);
  board_fill(board, width, height, mines, pos);
  printf("after fill\n");
  print_board(board, width, height);
}

