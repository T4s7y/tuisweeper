#include <stdlib.h>
#include <stdbool.h>

#pragma once

#define MAX_WIDTH 100;
#define MAX_HEIGHT 100;

typedef enum {
  MINE, TILE
} Tile_Type;

typedef struct {
  int x;
  int y; 
} Position;

typedef struct {
  Tile_Type type;
  Position pos; // The tiles coordinates
  int value;
  bool flag;
  bool revealed; // For printing purposes
} Tile;

typedef struct {
  Tile** tiles; // Array of tiles
  int width; // Board's width
  int height; // Board's height
  int mines; // Number of total mines in board
  Position first_pos; // The player's first played tile
} Board;

//typedef Tile** Board;

Board board_create(int width, int height, int mines, Position init_pos);

void board_fill(Board board);
