#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/board.h"

// Turns double index to single index
static int single_index(int x, int y, int max) {
  return x + y*max;
}

// Turns single index to double index
static Position double_index(int n, int max) {
  Position pos;
  pos.x = n % max;
  pos.y = n/max;
  return pos;
}

static void shuffle (int* array, int size) {
  for (int i = 0; i < size; i++) {
    int j = i + rand() / (RAND_MAX / (size-i) + 1);
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
  return;
}

static void update_value(Board board, Position pos) {
  for (int dx = (pos.x > 0 ? -1 : 0); dx <= (pos.x<board.width-1 ? 1 : 0); dx++) 
    for (int dy = (pos.y > 0 ? -1 : 0); dy <= (pos.y<board.height-1 ? 1 : 0); dy++) 
      if (dx != 0 || dy != 0) board.tiles[pos.x+dx][pos.y+dy].value++;
  return; 
}

void board_fill(Board board) {
  // Initialize an array with indexes and shuffle it to pick random spots for mines
  int index_array[board.width * board.height];
  for (int i = 0; i < board.width * board.height; i++) 
    //if (i != single_index(init_pos.x, init_pos.y, width)) 
    index_array[i] = i;
  
  shuffle(index_array, board.width * board.height);

  // Fill up the board with mines and update the surrounding tiles
  for (int i = 0; i < board.mines; i ++) {
    Position pos = double_index(index_array[i], board.width);
    if (pos.x == board.first_pos.x && pos.y == board.first_pos.y) 
      pos = double_index(index_array[board.mines], board.width);
    board.tiles[pos.x][pos.y].type= MINE ;
    update_value(board, pos);
  } 
  return;
}

Board board_create(int width, int height, int mines) {
  Board board;
  board.tiles = malloc(width*sizeof(Tile*));

  for (int i = 0; i < width; i++)
    board.tiles[i] = (Tile*)malloc(height * sizeof(Tile));
  // Initialize board with TILES 
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      board.tiles[i][j].type = TILE;
      board.tiles[i][j].pos.x = i;
      board.tiles[i][j].pos.y = j;
      board.tiles[i][j].value = 0;
      board.tiles[i][j].flag = false;
      board.tiles[i][j].cleared = false;
    }
  }
  board.width = width;
  board.height = height;
  board.mines = mines;
  board.cleared_tiles = malloc(sizeof(int));
  *board.cleared_tiles = 0;
  board.lost = malloc(sizeof(bool));
  *board.lost = false;
  Position pos;
  //we initialize first_pos with a random value in case the user doesn't set an acutal first position by clearing a mine 
  
  pos.x=(rand()%board.width)+1;
  pos.y=(rand()%board.height)+1;
  board.first_pos=pos;
  return board;
}

void board_destroy(Board board) {
  for (int i = 0; i < board.width; i++)
    free(board.tiles[i]);
  free(board.tiles);
  free(board.cleared_tiles);
  free(board.lost);
  return;
}

