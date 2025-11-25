#variables
#shortcuts
all: game board_test board.o board_print.o commands.o

beginner: game  
	./game beginner
intermediate: game  
	./game intermediate
expert: game  
	./game expert
run: game
	./game beginner

tests: board_test
	./board_test

clean : 
	rm *.o board_test game
#object files: 
	#src
board.o:src/board.c
	gcc -c src/board.c
	
board_print.o:src/board_print.c
	gcc -c src/board_print.c

commands.o: src/commands.c
	gcc -c src/commands.c

game.o:src/game.c
	gcc -c src/game.c
	#test
board_test.o:tests/board_test.c
	gcc -c tests/board_test.c

#executable
game: game.o board.o board_print.o commands.o
	gcc -o game game.o board.o board_print.o commands.o

board_test:board_test.o board.o board_print.o commands.o
	gcc -o board_test board.o board_print.o board_test.o commands.o

