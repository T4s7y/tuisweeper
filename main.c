/*board-gen.c*/
/* this program generates the mines board for the main game*/
#include<stdio.h>
#include<stdlib.h>
#include<random.h>
#include<stdint.h>
int8_t *[](int x, int y,int bombs,unsigned int seed ){
	/* to generate random numbers we will be taking in a seed and then incriment the seed every time we add a bomb
	if the function fails for whatever reason it returns a NULL pointer*/
	/*the first 4 bits are used to indicate how many bombs there are (aka 0-8) I will be doing this by using mod 8 
	to see how many bombs there are instead of taking the number itself*/

	/* making an empty board*/
	int8_t ** board= calloc(sizeof(int8_t*)*x);
	if (malloc==NULL){
		return NULL;
	}
	int i;
	for (i=0;i<x;i++){
		board[i]=calloc(sizeof(int8_t*)*y);	
		if (board[i]==NULL){
			return NULL;
		}
	}
	
	/*filling the board with random n
	

}
int main (){
	boardprint()
}


