# blackjack.c
An ultra-lightweight command-line based blackjack game

## File Structure

```
.
├── Makefile            # Build and clean the project
├── main.c              # Handles input/output and game object
├── blackjack.c         # Contains game logic and updates game object
├── blackjack.h         # Header file for blackjack.c
├── cards.c             # Manages card objects and deck functionality
├── cards.h             # Header file for cards.c
```

This blackjack game is implemented in three levels of abstraction. The cards are handled by cards.c, including creating new cards, initializing a deck of cards, drawing cards or adding them to a deck of cards. The second layer is the gamestate object handled by blackjack.c file. The gamestate object is initialized, updated and destroyed with the set of functions described in blackjack.h. The third layer is main.c, which handles user input, output and the gamestate object.

## Getting Started
This program was developed and tested on a linux machine, therefore it might not work on different machines. However, no machine-specific code was used, so it should compile just fine on a Windows machine.

### Compilation 
A Makefile is supplied for your convenience. Compile with `make` and clean with `make clean`.

This project was also designed to be able to be compiled with the command:
```
$ gcc -std=c99 -Wall -Wextra -pedantic *.c -o blackjack
```

### Running
If you used the Makefile to compile, run in your terminal:
```
$ ./blackjack
```

If you used any other method to compile, than it's your responsibility to find the name of the program.

### Uninstalling
Just delete this repo's directory from your computer. 
