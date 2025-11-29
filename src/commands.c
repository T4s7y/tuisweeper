#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/board.h"
#include "../include/commands.h"

bool check_command(mmask_t mouse, Board board, Position pos) {
  return ((mouse == BUTTON1_CLICKED || mouse == BUTTON3_CLICKED)
         && (pos.x > 0 && pos.x <= board.width && pos.y > 0 && pos.y <= board.height));
}

void command_translator(mmask_t mouse, Board board, Position pos){
  pos.x--;
  pos.y--;
  switch (mouse){
    case BUTTON1_CLICKED: 
        clear_tile(board, pos);
        break;
    case BUTTON3_CLICKED:
        flag_tile(board, pos);
        break;
  }
}

void clear_tile(Board board, Position pos) {
  if (board.tiles[pos.x][pos.y].flag)
    return;
  
  if (board.tiles[pos.x][pos.y].type == MINE) {
    *board.lost = true;
    return;
  }

  if (!board.tiles[pos.x][pos.y].cleared) {
  board.tiles[pos.x][pos.y].cleared = true;
  (*board.cleared_tiles)++;
  if (board.tiles[pos.x][pos.y].value == 0) 
    for (int dx = (pos.x > 0 ? -1 : 0); dx <= (pos.x<board.width-1 ? 1 : 0); dx++) 
      for (int dy = (pos.y > 0 ? -1 : 0); dy <= (pos.y<board.height-1 ? 1 : 0); dy++) 
        if (dx != 0 || dy != 0) 
          clear_tile(board, board.tiles[pos.x+dx][pos.y+dy].pos);
  }

  else {
    int flags = 0;
    for (int dx = (pos.x > 0 ? -1 : 0); dx <= (pos.x<board.width-1 ? 1 : 0); dx++) 
      for (int dy = (pos.y > 0 ? -1 : 0); dy <= (pos.y<board.height-1 ? 1 : 0); dy++) 
        if ((dx != 0 || dy != 0) && board.tiles[pos.x+dx][pos.y+dy].flag)
            flags++;
    if (flags != board.tiles[pos.x][pos.y].value)
      return;
    for (int dx = (pos.x > 0 ? -1 : 0); dx <= (pos.x<board.width-1 ? 1 : 0); dx++) 
      for (int dy = (pos.y > 0 ? -1 : 0); dy <= (pos.y<board.height-1 ? 1 : 0); dy++) 
        if ((dx != 0 || dy != 0) && !board.tiles[pos.x+dx][pos.y+dy].flag && !board.tiles[pos.x+dx][pos.y+dy].cleared) 
          clear_tile(board, board.tiles[pos.x+dx][pos.y+dy].pos);
  }
  return;
}

void flag_tile(Board board, Position pos) {
  if (board.tiles[pos.x][pos.y].cleared)
    return;
  *board.flags = (board.tiles[pos.x][pos.y].flag ? (*board.flags)-1 : (*board.flags)+1);
  board.tiles[pos.x][pos.y].flag = (board.tiles[pos.x][pos.y].flag ? false : true);
}



