#include <ncurses.h>
#include <stdlib.h> 

#include "board.h"

#pragma once

void print_board(Board board, WINDOW* board_win);

void print_command_list();
