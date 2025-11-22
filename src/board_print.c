#include <stdio.h>
#include <stdlib.h>

#include "../include/board.h"
#include "../include/board_print.h"

static void print_line(char middle,char edge, int lenght){
  printf("   ");
  printf("%c",edge);
    for (int j=0; j<lenght*2-1;j++)printf("%c",middle);
  printf("%c\n",edge);
}
void print_board(Board board) {
  char empty = ' ';
  char bomb = 'X';
  char flag = 'F';
  char horizontal_line='-';
  char vertical_line='|';
  char corners='+';
 //printing frist line of numbers
 printf("   ");
  for (int i=0;i<board.width;i++){
    if (i<9){
    printf(" %d",i+1);
    }
    else{
      printf(" %d",i+1);
    }
  }
  printf("\n");

  print_line(horizontal_line,corners,board.width);
  
  //board itself
  for (int i = 0; i < board.height; i++) {
    //printing vertical numbers
    if (i<9)
      printf("  %d",i+1);
    else if(i<99)
      printf (" %d",i+1);
    else
      printf("%d",i+1);

    for (int j = 0; j < board.width; j++) {
      if(board.tiles[j][i].flag)
        printf("%c%c",vertical_line,flag); 
      else if (!board.tiles[j][i].cleared) 
        printf("%c%c",vertical_line,empty);        
      else
        printf("%c%d",vertical_line, board.tiles[j][i].value);
    }

    printf("%c\n",vertical_line);
    if (i!=board.height-1)print_line(horizontal_line,vertical_line,board.width);
  }
  //final line
  print_line(horizontal_line,corners,board.width);
  return;
}


void print_command_list() {
  printf("Command list:\n"); 
  printf("c x_coordinate y_coordinate : clear tile on position(x_coordinate, y_coordinate)\n");
  printf("f x_coordinate y_coordinate : flag tile on position(x_coordinate y_coordinate)\n");
  printf("u x_coordinate y_coordinate : unflag tile on position(x_coordinate y_coordinate)\n");
  return;
}

