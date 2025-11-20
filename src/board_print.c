#include <stdio.h>
#include <stdlib.h>

#include "../include/board.h"
#include "../include/board_print.h"

void print_board(Board board, int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (board[j][i].type ==MINE)
        printf("|X");
      else 
        printf("|%d", board[j][i].value);
    }
    printf("|\n|");
    for (int j=0; j<width*2-1;j++)printf("-");
    printf("|\n");
  }
  return;
}
