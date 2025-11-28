#include <ncurses.h>
#include <stdlib.h>

#include "board.h" 

bool check_command(mmask_t mouse, Board board, Position pos); 

void command_translator(mmask_t mouse, Board board, Position pos);

void clear_tile(Board board, Position pos);

void flag_tile(Board board, Position pos);

