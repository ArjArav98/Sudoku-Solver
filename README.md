# Introduction
These are a suite of C++ programs which deal with Sudoku Puzzles. The name might be misleading, yes, but these programs don't just solve Sudoku puzzles, they also achieve other objectives such as Sudoku Puzzle Validation and Sudoku Puzzle Generation (Under development).

## Contents
* [Sudoku Solver](#sudoku-solver)
    * [Getting Started (Usage)](#getting-started)
    * [How It Works](#how-it-works)
* [Sudoku Validator](#sudoku-validator)
    * [Getting Started (Usage)](#getting-started-1)
    * [How It Works](#how-it-works-1)
* [Acknowledgements](#acknowledgements)
* [Tools](#tools)

# Sudoku-Solver
This is a program which solves 9x9 Sudoku puzzles. **Written completely in C++** and **built wholly from scratch**, this program reads input either from a user or from a file containing the Sudoku values and solves the puzzle. It employs concepts such as backtracking and recursion.

### Getting Started
* Simply download the ```sudoku-solver.cpp``` file found in the ```Sudoku-Solver/``` directory. Run it using any standard C++ compiler. In case of any errors or compatibility issues, submit an issue in this git.
* Once downloaded, compiled and run; the program will require the user to input the Sudoku puzzle into it. There are two ways to do this.
    * The user can either input the values manually one-by-one when the program is running.
    * The user can write all the values into a file, seperated by whitespaces. The file can have any name or extension. When the program is running, the user will be prompted to simply enter the name of the file (with extension). **Below** is an example of how the contents of such a file might look. Look at the ```sample.txt``` files in the same directory for more examples.
    
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

* Once solved, the Sudoku puzzles shall be displayed like this.
    ```
    ++=====================================++
    || 1   7   2 || 5   4   9 || 6   8   3 ||
    ++-----------++-----------++-----------++
    || 6   4   5 || 8   7   3 || 2   1   9 ||
    ++-----------++-----------++-----------++
    || 3   8   9 || 2   6   1 || 7   4   5 ||
    ++=====================================++
    || 4   9   6 || 3   2   7 || 8   5   1 ||
    ++-----------++-----------++-----------++
    || 8   1   3 || 4   5   6 || 9   7   2 ||
    ++-----------++-----------++-----------++
    || 2   5   7 || 1   9   8 || 4   3   6 ||
    ++=====================================++
    || 9   6   4 || 7   1   5 || 3   2   8 ||
    ++-----------++-----------++-----------++
    || 7   3   1 || 6   8   2 || 5   9   4 ||
    ++-----------++-----------++-----------++
    || 5   2   8 || 9   3   4 || 1   6   7 ||
    ++=====================================++
    ```

### How It Works
This particular algorithm employs the use of backtracking, one of the more common methods to solve Sudoku puzzles. I've written a simple algorithm to give an idea of how the program works.

1. Start.
2. We start with the first empty cell.
3. We generate a list of possible valid values that can be filled in that cell.
4. We iterate over this list and start with the first value. This value is placed in the required cell.
5. We move on to the next cell. We again generate a list of possibilities. However, if no list can be generated, then this means that there is something wrong with the value of the previous cell. We then move back to the previous cell and place the next value on the generated list in the cell now. We repeat this step until the current cell has a valid value placed inside it.
6. We stop when we reach the 81st cell (the last cell in a Sudoku puzzle) and have placed a valid value.
7. The puzzle has now been solved.
8. Stop.

# Sudoku Validator
This is a program which validates solutions for 9x9 Sudoku puzzles. **Written completely in C++** and **built wholly from scratch**, this program takes in input from the user or from a file containing the values. It then validates the puzzle and then displays whether it is a valid solution or not.

### Getting Started
* Simply download the ```sudoku-validator.cpp``` file found in the ```Sudoku-Validator``` directory. Run it using any standard C++ compiler. In case of any errors or compatibility issues, submit an issue in this git.
* Once downloaded, compiled and run; the program will require the user to input the Sudoku puzzle into it. There are two ways to do this.
    * The user can either input the values manually one-by-one when the program is running.
    * The user can write all the values into a file, seperated by whitespaces. The file can have any name or extension. When the program is running, the user will be prompted to simply enter the name of the file (with extension). **Below** is an example of how the contents of such a file might look. Look at the ```sample.txt``` files in the same directory for more examples.
    
        ```
        8 4 6  9 3 7  1 5 2
        3 1 9  6 2 5  8 4 7
        7 5 2  1 8 4  9 6 3
        
        2 8 5  7 1 3  6 9 4
        4 6 3  8 5 9  2 7 1
        9 7 1  2 4 6  3 8 5
        
        1 2 7  5 9 8  4 3 6
        6 3 8  4 7 1  5 2 9
        5 9 4  3 6 2  7 1 8
        ```


### How It Works
The workings of the Sudoku Validator are quite simple, to be honest. Here's a simple algorithm explaining them all.

1. Start
2. The values in all the cells are checked to see if they are in the range 1-9. If not, the puzzle is invalid.
3. Every row is checked to see if it contains 1-9 atleast once. If not, the solution is invalid.
4. Every column is checked to see if it contains 1-9 atleast once. If not, the solution is invalid.
4. Every 3x3 grid is checked to see if it contains 1-9 atleast once. If not, the solution is invalid.
5. If all the criteria have been satisfied, the solution is valid.
6. Stop

## Future Direction

* Right now, the Sudoku Solver Suite is just a CLI application with a I/O interface. However, if we could make it into a CLI utility which takes in inputs through parameters and switches, that would make it easier for other developers to reuse.

## Acknowledgements

* Shriram R - Idea Inspiration
* Aravind B - Puzzle Display Design Ideas

## Tools
* Vim Editor
* Clang C++ Compiler
