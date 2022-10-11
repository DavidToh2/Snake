# C++ Snake game

<br>

## Part I: Snake Simulation

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

<br>

$\displaystyle\sum_{i=0}^{n}\left(\sum_{cyc} a^{i}b(a-b) + b^{i}c(b-c) + c^{i}a(c-a)\right) = $ cool math equation

<br>

## Part II: Actual Snake Game

[Tutorial 1: lazyfoo.com](https://lazyfoo.net/tutorials/)

[Tutorial 2: thenumb.at](https://thenumb.at/cpp-course/index.html)