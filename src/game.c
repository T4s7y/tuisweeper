#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "../include/board.h"
#include "../include/board_print.h"
#include "../include/commands.h"

#define MAX_WIDTH 100
#define MAX_HEIGHT 100


static bool consume_rest_of_line(void) {
  int has_extra_char=false; 
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF) {
    if (ch!=' ')has_extra_char=true;
  }
  return has_extra_char;
}

// User enters width, height and number of mines 
int main(int argc, char* argv[]) {
  srand(time(NULL));
  if (argc != 4) {
    printf("Enter board's dimensions(width, height) and number of mines\n");
    return 1;
  }
  int width = atoi(argv[1]);
  if (width <= 0 || width >= MAX_WIDTH) {
    printf("Invalid width\n");
    return 1;
  }

  int height = atoi(argv[2]);
  if (height <= 0 || height >= MAX_HEIGHT) {
    printf("Invalid height\n");
    return 1;
  }

  int mines = atoi(argv[3]);
  if (mines <= 0 || mines >= width*height) {
    printf("Invalid amount of mines\n");
    return 1;
  }

  bool win = false;
  Board board = board_create(width, height, mines);
  print_board(board);  

  //in c scanf will get triggered automatically so long as stdin has characterss left, leading to weird behavior when the user inputs unexpected values, to combat this thie "confume rest of line"function practically delets the remaining input after the "first"scanf but that means that commands with garbage after the correct command (ex: c 2 1 asolidfasjflisjfsjij) would be valid, so consume_rest_of_line will return 1 if it actually has to consume somehting and then store it to has_extra_char.
  bool first_round = true;
  bool has_extra_char;
  char command;
  Position pos;
  while (!win) {
    int input = scanf("%c %d %d", &command, &pos.x, &pos.y);
    has_extra_char = consume_rest_of_line();
    while (has_extra_char||input != 3 || !check_command(board, command, pos)) {
      printf("Invalid command\n");
      print_command_list();
      input = scanf("%c %d %d", &command, &pos.x, &pos.y);
      has_extra_char=consume_rest_of_line();
    }
    pos.x--;
    pos.y--;
    if (first_round) {
      board.first_pos = pos; 
      board_fill(board);
      first_round = false;
    }
    command_translator(command,board,pos);
    if (*board.lost == true) {
      print_board(board);
      break;
    }
    print_board(board);
    if ((*board.cleared_tiles + board.mines) == board.width*board.height) {
      win = true;
      printf("You did something\n");
    }
  }

  board_destroy(board);
  return 0;
}
