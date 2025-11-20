
#shortcuts
all: board_test board.o board_print.o

run:all
	./board_test

clean : 
	rm *.o board_test
#object files: 
	#src
board.o:src/board.c
	gcc -c src/board.c
	
board_print.o:src/board_print.c
	gcc -c src/board_print.c
	#test
board_test.o:tests/board_test.c
	gcc -c tests/board_test.c

#executable
board_test:board_test.o board.o board_print.o
	gcc -o board_test board.o board_print.o board_test.o

