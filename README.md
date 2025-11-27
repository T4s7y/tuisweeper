# CliSweeper

clisweeper is a cli-controlled game reminiscent (but legally distinct) to the classic pc game [minesweeper](https://en.wikipedia.org/wiki/Minesweeper_(video_game))

## Installation

clone the repository using the following command 

```bash
git clone https://github.com/username-temporary/clisweeper
cd clisweeper
make install
```
alternatively to compile it and run it without adding it to usr/bin as follows:
```bash
git clone https://github.com/username-temporary/clisweeper
cd clisweeper
make game 
```
## uninstall
while in the directory where the repository was cloned 
```bash
make uninstall
cd ..
rm -rf clisweeper 
```

## Usage
```bash
clisweeper [difficulty] 
valid difficulties are: beginner,intermediate,expert
clisweeper [width] [height] [mines]
```
## Gameplay 
after a difficulty has been selected the game will print out a board on the terminal, during gameplay there are 3 valid commands: 
```bash
c [x coordinate] [y coordinate]
```
will clear the tile in position (x,y)  (the outer numbers can be used to find coordinates easier)
```bash
f [x coordinate] [y coordinate]
```
will set a flag on the tile in position (x,y)
```bash
u [x coordinate] [y coordinate]
```
will un-flag the tile on position (x,y) if there's already a flag on said tile 
## Example gameplay 
```
clisweeper beginner
    1 2 3 4 5 6 7 8 9 10
   +-------------------+
  1| | | | | | | | | | |
   |-------------------|
  2| | | | | | | | | | |
   |-------------------|
  3| | | | | | | | | | |
   |-------------------|
  4| | | | | | | | | | |
   |-------------------|
  5| | | | | | | | | | |
   |-------------------|
  6| | | | | | | | | | |
   |-------------------|
  7| | | | | | | | | | |
   |-------------------|
  8| | | | | | | | | | |
   |-------------------|
  9| | | | | | | | | | |
   |-------------------|
 10| | | | | | | | | | |
   +-------------------+
c 5 5 
    1 2 3 4 5 6 7 8 9 10
   +-------------------+
  1| | | | | | | |1|0|0|
   |-------------------|
  2| | | | |2|1|1|1|0|0|
   |-------------------|
  3| | | | |1|0|0|0|0|0|
   |-------------------|
  4| | |2|2|1|0|0|0|0|0|
   |-------------------|
  5| | |1|0|0|0|0|1|1|1|
   |-------------------|
  6| | |1|0|0|1|1|2| | |
   |-------------------|
  7| |2|1|0|0|1| |2|1|1|
   |-------------------|
  8| |1|0|0|0|1|1|1|0|0|
   |-------------------|
  9| |1|0|0|0|0|0|0|0|0|
   |-------------------|
 10| |1|0|0|0|0|0|0|0|0|
   +-------------------+
f 4 3 
    1 2 3 4 5 6 7 8 9 10
   +-------------------+
  1| | | | | | | |1|0|0|
   |-------------------|
  2| | | | |2|1|1|1|0|0|
   |-------------------|
  3| | | |F|1|0|0|0|0|0|
   |-------------------|
  4| | |2|2|1|0|0|0|0|0|
   |-------------------|
  5| | |1|0|0|0|0|1|1|1|
   |-------------------|
  6| | |1|0|0|1|1|2| | |
   |-------------------|
  7| |2|1|0|0|1| |2|1|1|
   |-------------------|
  8| |1|0|0|0|1|1|1|0|0|
   |-------------------|
  9| |1|0|0|0|0|0|0|0|0|
   |-------------------|
 10| |1|0|0|0|0|0|0|0|0|
   +-------------------+
u 4 3
    1 2 3 4 5 6 7 8 9 10
   +-------------------+
  1| | | | | | | |1|0|0|
   |-------------------|
  2| | | | |2|1|1|1|0|0|
   |-------------------|
  3| | | | |1|0|0|0|0|0|
   |-------------------|
  4| | |2|2|1|0|0|0|0|0|
   |-------------------|
  5| | |1|0|0|0|0|1|1|1|
   |-------------------|
  6| | |1|0|0|1|1|2| | |
   |-------------------|
  7| |2|1|0|0|1| |2|1|1|
   |-------------------|
  8| |1|0|0|0|1|1|1|0|0|
   |-------------------|
  9| |1|0|0|0|0|0|0|0|0|
   |-------------------|
 10| |1|0|0|0|0|0|0|0|0|
   +-------------------+
```
## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.


## License

[MIT](https://choosealicense.com/licenses/mit/)
