#variables
CC=gcc 
CFLAGS=-Wall -Werror -Iinclude
LDLIBS=-lncurses -ltinfo
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

vpath %.c src/
vpath %.c tests/
vpath %.h include/

#shortcuts
all: game board_test

#install and uninstall
install: game
	sudo cp $(ROOT_DIR)/game /usr/bin/tuisweeper
uninstall:
	sudo rm /usr/bin/tuisweeper

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
	rm -f *.o board_test game


#src
board.o: board.h
board_print.o: board_print.h board.h
commands.o: commands.h 
game.o: board.h board_print.h commands.h
#test
board_test.o: board_print.h 

#executable
game: board.o board_print.o commands.o
board_test: board.o board_print.o commands.o

