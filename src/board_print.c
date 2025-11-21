#include <stdio.h>
#include <stdlib.h>

#include "../include/board.h"
#include "../include/board_print.h"

void print_board(Board board) {
  for (int i = 0; i < board.height; i++) {
    for (int j = 0; j < board.width; j++) {
      if (board.tiles[j][i].type ==MINE)
        printf("|X");
      else 
        printf("|%d", board.tiles[j][i].value);
    }
    printf("|\n|");
    for (int j=0; j<board.width*2-1;j++)printf("-");
    printf("|\n");
  }
  return;
}
