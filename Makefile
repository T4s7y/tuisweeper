#variables
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
#install and uninstall
#install: game
#	sudo cp $(ROOT_DIR)/game /usr/bin/tuisweeper
#uninstall:
#	sudo rm /usr/bin/tuisweeper

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
	gcc -c src/board_print.c -lncurses

commands.o: src/commands.c
	gcc -c src/commands.c

game.o:src/game.c
	gcc -c src/game.c -lncurses
	#test
board_test.o:tests/board_test.c
	gcc -c tests/board_test.c

#executable
game: game.o board.o board_print.o commands.o
	gcc -o game game.o board.o board_print.o commands.o -lncurses
	
board_test:board_test.o board.o board_print.o commands.o
	gcc -o board_test board.o board_print.o board_test.o commands.o -lncurses

