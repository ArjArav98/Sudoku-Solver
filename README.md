# Sudoku-Solver
These are a suite of C++ programs which deal with Sudoku Puzzles. The name might be misleading, yes, but these programs don't just solve Sudoku puzzles, they also achieve other objectives such as Sudoku Generation, Sudoku Validation (all under development).

## Sudoku-Solver
This is a program which solves 9x9 Sudoku puzzles. **Written completely in C++** and **built wholly from scratch**, this program reads input either from a user or from a file containing the Sudoku values and solves the puzzle. It employs concepts such as backtracking and recursion.

### Getting Started
* Simply download the ```sudoku-solver.cpp``` file found in the ```Sudoku-Solver``` directory. Run it using any standard C++ compiler. In case of any errors or compatibility issues, submit an issue in this git.
* Once downloaded, compiled and run; the program will require the user to input the Sudoku puzzle into it. There are two ways todo this. The user can either input the values manually one-by-one or can write all the values into a file, seperated by whitespaces. Below is an example of how the contents of such a file might look.

```
0 0 0  0 0 0  6 8 0
0 0 0  0 7 3  0 0 9
3 0 9  0 0 0  0 4 5

4 9 0  0 0 0  0 0 0
8 0 3  0 5 0  9 0 2
0 0 0  0 0 0  0 3 6

9 6 0  0 0 0  3 0 8
7 0 0  6 8 0  0 0 0
0 2 8  0 0 0  0 0 0
```
Files can have any name or extension.

* Once solved, the Sudoku puzzles shall be displayed like this.
```
+---+---+---+---+---+---+---+---+---+
| 1 | 7 | 2 | 5 | 4 | 9 | 6 | 8 | 3 |
+---+---+---+---+---+---+---+---+---+
| 6 | 4 | 5 | 8 | 7 | 3 | 2 | 1 | 9 |
+---+---+---+---+---+---+---+---+---+
| 3 | 8 | 9 | 2 | 6 | 1 | 7 | 4 | 5 |
+---+---+---+---+---+---+---+---+---+
| 4 | 9 | 6 | 3 | 2 | 7 | 8 | 5 | 1 |
+---+---+---+---+---+---+---+---+---+
| 8 | 1 | 3 | 4 | 5 | 6 | 9 | 7 | 2 |
+---+---+---+---+---+---+---+---+---+
| 2 | 5 | 7 | 1 | 9 | 8 | 4 | 3 | 6 |
+---+---+---+---+---+---+---+---+---+
| 9 | 6 | 4 | 7 | 1 | 5 | 3 | 2 | 8 |
+---+---+---+---+---+---+---+---+---+
| 7 | 3 | 1 | 6 | 8 | 2 | 5 | 9 | 4 |
+---+---+---+---+---+---+---+---+---+
| 5 | 2 | 8 | 9 | 3 | 4 | 1 | 6 | 7 |
+---+---+---+---+---+---+---+---+---+
```

### How It Works
This particular algorithm employs the use of backtracking, one of the more common methods to solve Sudoku puzzles. I've written a simple algorithm to give an idea of how the program works.

1. Start
2. We start with the first empty cell.
3. We generate a list of possible valid values that can be filled in that cell.
4. We iterate over this list and start with the first value. This value is placed in the required cell.
5. We move on to the next cell. We again generate a list of possibilities. However, if no list can be generated, then this means that there is something wrong with the value of the previous cell. We then move back to the previous cell and place the next value on the generated list in the cell now. We repeat this step until the current cell has a valid value placed inside it.
6. We stop when we reach the 81st cell (the last cell in a Sudoku puzzle) and have placed a valid value.
7. The puzzle has now been solved.
8. Stop

### Tools
* Vim Editor
* Clang C++ Compiler
