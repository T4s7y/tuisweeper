#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../include/board.h"

static int single_index(int x, int y, int max) {
  return x + y*max;
}

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

static void update_value(Board board, Position pos, int width, int height) {
  if (pos.y+1<height) board[pos.x][pos.y+1].value++;
  if (pos.x+1<width)  board[pos.x+1][pos.y].value++;
  if (pos.y>0) board[pos.x][pos.y-1].value++;
  if (pos.x>0) board[pos.x-1][pos.y].value++;
  if (pos.x != 0 && pos.y != 0) board[pos.x-1][pos.y-1].value++;
  if (pos.x != 0 && pos.y+1 < height) board[pos.x-1][pos.y+1].value++;
  if (pos.x != width-1 && pos.y+1 < height) board[pos.x+1][pos.y+1].value++;
  if (pos.x != width-1 && pos.y != 0) board[pos.x+1][pos.y-1].value++;
  return; 
}

void board_fill(Board board, int width, int height, int mines, Position init_pos) {
  // Initialize an array with indexes and shuffle it to pick random spots for mines
  int index_array[width*height];
  for (int i = 0; i < width * height; i++) 
    //if (i != single_index(init_pos.x, init_pos.y, width)) 
    index_array[i] = i;
  
  shuffle(index_array, width * height);

  // Fill up the board with mines and update the surrounding tiles
  for (int i = 0; i < mines; i ++) {
    Position pos = double_index(index_array[i], width);
    board[pos.x][pos.y].type= MINE ;
    board[pos.x][pos.y].value=5;
    update_value(board, pos, width, height);
  } 
  return;
}

Board board_create(int width, int height, int mines, Position init_pos) {
  // Change Board to be a 1d array instead and use one index
  Board board = malloc(width*sizeof(Tile*));

  for (int i = 0; i < width; i++)
    board[i] = (Tile*)malloc(height * sizeof(Tile));
  // Initialize board with TILES 
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      Tile curr_tile = board[i][j];
      curr_tile.type = 1;
      curr_tile.pos.x = i+1;
      curr_tile.pos.y = j+1;
      curr_tile.value = 0;
      curr_tile.flag = false;
      curr_tile.revealed = false;
      board[i][j]= curr_tile;
    }
  }
  return board;
}
