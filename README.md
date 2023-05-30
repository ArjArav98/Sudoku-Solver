# Sudoku-Suite
A C++17-compatible header that provides useful functions which help with the solving, validation and generation of 9x9 Sudoku puzzles. 

## Contents
* [Usage](#usage)
* [Documentation](#documentation)
* [Examples](#examples)
    * [Solving and validating a Sudoku puzzle](#solving-and-validating-sudoku-puzzle)
    * [Generating a Sudoku puzzle](#generating-a-sudoku-puzzle)
    * [Initialising and reusing Grid objects](#initialising-and-reusing-grid-objects)
    * [Reading Sudoku puzzles from a file](#reading-sudoku-puzzles-from-a-file)
    * [Operations on Grid objects](#operations-on-grid-objects)
* [How It Works](#sudoku-solver---how-it-works)
* [Running Tests](#running-tests)
* [Acknowledgements](#acknowledgements)
* [Tools](#tools)

## Usage 

* Download the files in the `src/` directory and move it to your project's directory.
* Include the required header files, as shown below in the examples, and use the functions you need!
* **NOTE:** The code is incompatible with pre-C++17 versions. While compiling, you'll have to compile with the `--std=c++17` flag.
    * For example; when using the clang compiler, the compile command would be `c++ --std=c++17 /path/to/file.cpp`

## Documentation

There are **three functions** that Sudoku-Suite provides the developer, along with **one class**. They are as follows:-

* `Grid`
    *  An object that represents a 9x9 Sudoku grid. The `Grid` object does not validate the grid in any way, i.e, it only holds the grid and values inside it.
    * While initialising, if the given values are invalid, an `std::invalid_argument` exception is thrown.
    * *Check out the examples below to see how we can initialise and use this object!*
* `void solve(Grid *grid)`
    *  A function that takes in a pointer to a `Grid` object and solves the Sudoku puzzle present in it. Returns nothing.
    * If the puzzle cannot be solved, a `std::logic_error` exception is thrown.
* `bool is_valid_solution(Grid &grid)`
    *  A function that takes in a `Grid` object and returns a `bool` with a value of `true` if the `Grid` object contains a finished and valid Sudoku solution. 
* `Grid generate_puzzle()`
    *  A function that takes in nothing and returns a `Grid` object containing an unfinished Sudoku puzzle.

## Examples

**NOTE:** The following examples are also present in the repository in the `examples/` directory.

* [Solving and validating a Sudoku puzzle](#solving-and-validating-sudoku-puzzle)
* [Generating a Sudoku puzzle](#generating-a-sudoku-puzzle)
* [Initialising and reusing Grid objects](#initialising-and-reusing-grid-objects)
* [Reading Sudoku puzzles from a file](#reading-sudoku-puzzles-from-a-file)
* [Operations on Grid objects](#operations-on-grid-objects)

#### Solving and validating Sudoku puzzle
```
#include<iostream>
#include"/path/to/src/sudoku_solver.h"
#include"/path/to/src/sudoku_validator.h"

int main() {
    sudoku::Grid grid({{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }}, // The 0s represent blank cells.
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }});

    sudoku::solve(&grid);

    std::cout << "Solution is valid? --> ";
    std::cout << sudoku::is_valid_solution(grid) << std::endl;
    
    std::cout << grid << std::endl;

    return 0;
}
```

#### Generating a Sudoku puzzle 
```
#include<iostream>
#include"/path/to/src/sudoku_generator.h"

int main() {
    sudoku::Grid grid = sudoku::generate_puzzle();
    std::cout << grid << std::endl;

    return 0;
}
```

#### Initialising and reusing Grid objects 
```
#include<iostream>
#include"/path/to/src/grid.h"

/* NOTE: If you only need to utilise the Grid object,
 * you can just import the "grid.h" header alone. */

int main() {
    //================
    // Method 1: Use the constructor and pass in a
    // 2D matrix of values.
    //================
    
    sudoku::Grid grid({{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }});
    std::cout << grid << std::endl;
    
    //================
    // Method 2: Declare a 2D matrix of values and pass it
    // into the set_initial_state() method.
    //================

    std::array<std::array<int, 9>, 9> values = {{
        {{ 9, 7, 8, 4, 1, 0, 0, 0, 5 }},
        {{ 3, 0, 0, 8, 0, 0, 0, 6, 4 }},
        {{ 6, 0, 0, 3, 5, 0, 0, 9, 0 }},
        {{ 2, 6, 9, 0, 3, 0, 0, 0, 7 }},
        {{ 5, 0, 7, 1, 0, 0, 0, 0, 0 }},
        {{ 1, 0, 3, 0, 0, 2, 0, 8, 9 }},
        {{ 7, 1, 0, 2, 0, 5, 0, 0, 3 }},
        {{ 0, 0, 2, 7, 0, 3, 1, 5, 8 }},
        {{ 0, 0, 5, 9, 4, 1, 0, 0, 0 }}
    }};
    grid.set_initial_state(values);
    std::cout << grid << std::endl;

    //================
    // Method 3: Read the initial state of the puzzle
    // from a file.
    //================
    
    grid.set_initial_state_from_file("path/to/sample1.txt");
    std::cout << grid << std::endl;

    return 0;
}
```

#### Reading Sudoku puzzles from a file 

File: `sample1.txt`
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

```
#include<iostream>
#include"/path/to/src/grid.h"

/* NOTE: If you only need to utilise the Grid object,
 * you can just import the "grid.h" header alone. */

int main() {
    sudoku::Grid grid;
    grid.set_initial_state_from_file("sample1.txt");
    std::cout << grid << std::endl;

    sudoku::solve(&grid);
    std::cout << grid << std::endl;

    return 0;
}
```

#### Operations on Grid objects 
```
#include<iostream>
#include"/path/to/src/grid.h"

/* NOTE: If you only need to utilise the Grid object,
 * you can just import the "grid.h" header alone. */

int main() {

    sudoku::Grid sample_grid_1({{
        {{ 1, 7, 2, 5, 4, 9, 6, 8, 3 }},
        {{ 6, 4, 5, 8, 7, 3, 2, 1, 9 }},
        {{ 3, 8, 9, 2, 6, 1, 7, 4, 5 }},
        {{ 4, 9, 6, 3, 2, 7, 8, 5, 1 }},
        {{ 8, 1, 3, 4, 5, 6, 9, 7, 2 }},
        {{ 2, 5, 7, 1, 9, 8, 4, 3, 6 }},
        {{ 9, 6, 4, 7, 1, 5, 3, 2, 8 }},
        {{ 7, 3, 1, 6, 8, 2, 5, 9, 4 }},
        {{ 5, 2, 8, 9, 3, 4, 1, 6, 7 }}
    }});
    
    sudoku::Grid sample_grid_2({{
        {{ 1, 7, 2, 5, 4, 9, 6, 8, 3 }},
        {{ 6, 4, 5, 8, 7, 3, 2, 1, 9 }},
        {{ 3, 8, 9, 2, 6, 1, 7, 4, 5 }},
        {{ 4, 9, 6, 3, 2, 7, 8, 5, 1 }},
        {{ 8, 1, 3, 4, 5, 6, 9, 7, 2 }},
        {{ 2, 5, 7, 1, 9, 8, 4, 3, 6 }},
        {{ 9, 6, 4, 7, 1, 5, 3, 2, 8 }},
        {{ 7, 3, 1, 6, 8, 2, 5, 9, 4 }},
        {{ 5, 2, 8, 9, 3, 4, 1, 6, 7 }}
    }});

    if (sample_grid_1 == sample_grid_2) std::cout << "They're the same! \n\n";

    // Get grid value for coordinate.
    std::pair<int, int> last_coord = std::make_pair(8, 8);
    int last_value = sample_grid_1.get(last_coord);

    // Print the grid to the console.
    std::cout << sample_grid_2 << std::endl;

    return 0;
}
```

### Sudoku Solver - How It Works
This particular algorithm employs the use of backtracking, one of the more common methods to solve Sudoku puzzles. I've written a simple algorithm to give an idea of how the program works.

1. Start.
2. We start with the first empty cell.
3. We generate a list of possible valid values that can be filled in that cell.
4. We iterate over this list and start with the first value. This value is placed in the required cell.
5. We move on to the next cell. We again generate a list of possibilities. However, if no list can be generated, then this means that there is something wrong with the value of the previous cell. We then move back to the previous cell and place the next value on the generated list in the cell now. We repeat this step until the current cell has a valid value placed inside it.
6. We stop when we reach the 81st cell (the last cell in a Sudoku puzzle) and have placed a valid value.
7. The puzzle has now been solved.
8. Stop.

## Running Tests
* To run the tests, enter `c++ --std=c++17 tests/test_sudoku_suite.cpp` and then run the executable produced.

## Acknowledgements

* Shriram R - Idea Inspiration
* Aravind B - Puzzle Display Design Ideas

## Tools
* Vim Editor
* Clang C++ Compiler
