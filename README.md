# C++ Snake game

## Part I: Actual Snake Game

Snake game built in C++ using SDL. The objective of this project is to familiarise myself with coding exportable/re-usable modules and overall project structure.

### Game files:

- `snake.cpp`: overarching module containing the main game loop.

    - This module includes all the other module headers.

- `attributes.cpp`, `attributes.h`: config module containing global/extern variables, enum classes, as well as spritemap name and coordinate data. This module is included in all the files.

- `game.cpp`, `game.h`: module containing definitions and declarations of the `Game` class and its member functions, which handle game logic, as well as internal variables. The class object also outputs game data and state information for other modules to handle.

    - This module is only included in `snake.cpp`.

- `graphics.cpp`, `graphics.h`: controls background, active sprites and (TBA) menu display. The module handles sprite name selection and coordinate generation, and passes the information to `renderer`.

    - This module is only included in `snake.cpp`, and includes `renderer.h`.

- `renderer.cpp`, `renderer.h`: a basic rendering engine containing definitions and declarations of the `renderEngine` class and its member functions and internal variables. The class object and its functions handle `surface->texture->renderer` blitting. The `imageCache` sub-class handles memory initialisation and (de)-allocation for the game sprites.

    - This module is only included in `graphics.cpp` and `snake.cpp`. This module includes the `SDL.h` and `SDL_image.h` libraries.

- `events.cpp`, `events.h`: module that receives and parses user inputs with the aid of the SDL library. User inputs are parsed into the `enum class events` type, before being sent back to the main game loop.

    - This module is only included in `snake.cpp`.

[Tutorial 1: lazyfoo.com](https://lazyfoo.net/tutorials/)

[Tutorial 2: thenumb.at](https://thenumb.at/cpp-course/index.html)

## Part II: Snake Simulation

**Problem: Simulate a Snake game.**

You are given a series of inputs representing a sequence of in-game events.

The first line consists of four integers $r, c, y, x.$ The board is $c$ columns by $r$ rows large, and the snake's starting position is column $x$ and row $y$. Take the bottom-left cell to be $(0, 0)$. Assume the snake starts facing right.

Each of the following lines could be one of five possible inputs:
- F: move forward one unit.
- L: turn left. (No movement.)
- R: turn right. (No movement.)
- S $y$ $x$: spawn a fruit at the cell in row $y$ and column $x$;
- E: (manually) end game.

Your output should consist of two parts:
- "DEAD" if the player dies before the end of the sequence; "ALIVE" if the player is still alive
- followed by the player's score.

**Implementation:** Basically complete, but I don't know how to process competition-style inputs efficiently. For now it just uses `cin`.

To look at methods of input via `.txt` and `.ini` files in the future.


$$ \sum_{i=0}^{n}\left(\sum_{cyc} a^{i}b(a-b) + b^{i}c(b-c) + c^{i}a(c-a)\right) = \text{cool math equation} $$ 

Note that "displaystyle" doesn't work on github.

<br>
