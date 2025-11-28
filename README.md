# TuiSweeper

tui sweeper is a fork of clisweeper, cli-controlled game reminiscent (but legally distinct) to the classic pc game [minesweeper](https://en.wikipedia.org/wiki/Minesweeper_(video_game)) 
that uses the terminal user interface library [Ncurses](https://en.wikipedia.org/wiki/Ncurses)

## Installation

clone the repository using the following command 

```bash
git clone https://github.com/T4s7y/tuisweeper
cd tuisweeper
make install
```
alternatively to compile it and run it without adding it to usr/bin as follows:
```bash
git clone https://github.com/username-temporary/tuisweeper
cd tuisweeper
make game 
```
## uninstall
while in the directory where the repository was cloned 
```bash
make uninstall
cd ..
rm -rf tuisweeper 
```

## Usage
```bash
tuisweeper [difficulty] 
valid difficulties are: beginner,intermediate,expert
tuisweeper [width] [height] [mines]
```
## Gameplay 
unlike cliweeper, tui sweeper is exclusively controlled via mouse input, left click to clear a tile, right click to set a flag and then right click again on a flag to remove it 


## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.


## License

[MIT](https://choosealicense.com/licenses/mit/)
