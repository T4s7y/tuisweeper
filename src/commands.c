#include <stdlib.h>
#include <stdio.h>

#include "../include/board.h"
#include "../include/commands.h"

bool check_command(Board board, char command, Position pos) {
  return ((command == 'c' || command == 'C' || command == 'f' || command == 'F' || command == 'u' || command == 'U')
         && (pos.x > 0 && pos.x <= board.width && pos.y > 0 && pos.y <= board.height));
}

void command_translator(char input,Board board,Position pos){
  switch (input){
    case 'c': 
    case 'C':
        clear_tile(board, pos);
        break;
    case 'f':
    case 'F':
        flag_tile(board, pos);
        break;
    case 'u':
    case 'U':
        unflag_tile(board, pos);
        break;
  }
}
void clear_tile(Board board, Position pos) {
  if (board.tiles[pos.x][pos.y].flag){
    printf("this tile is flagged, unflag it if you would like to clear it \n");
    return;
  }
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
    else 
      for (int dx = (pos.x > 0 ? -1 : 0); dx <= (pos.x<board.width-1 ? 1 : 0); dx++) 
        for (int dy = (pos.y > 0 ? -1 : 0); dy <= (pos.y<board.height-1 ? 1 : 0); dy++) 
          if ((dx != 0 || dy != 0) && !board.tiles[pos.x+dx][pos.y+dy].flag && !board.tiles[pos.x+dx][pos.y+dy].cleared) 
            clear_tile(board, board.tiles[pos.x+dx][pos.y+dy].pos);
  }
  return;
}

void flag_tile(Board board, Position pos) {
  if (!board.tiles[pos.x][pos.y].cleared)
    board.tiles[pos.x][pos.y].flag = true;
  else
    printf("This tile is cleared, it cannot be flagged\n");
  return;
}

void unflag_tile(Board board, Position pos) {
  if (board.tiles[pos.x][pos.y].flag)
    board.tiles[pos.x][pos.y].flag = false;
  else 
    printf("This tile is not flagged, it cannnot be unflagged\n");
  return;
}



