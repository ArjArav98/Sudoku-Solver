/* Copyright 2023 Arjun Aravind */
/* A basic example as seen in the project's README. */

#include<iostream>
#include"../src/sudoku_solver.h"
#include"../src/sudoku_validator.h"

int main() {
    sudoku::Grid grid({{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},  // The 0s represent blank cells.
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

    std::cout << grid << std::endl;

    if (sudoku::is_valid_solution(grid)) {
        std::cout << "Solution is valid!\n";
    } else {
        std::cout << "DEFCON 4! Something isn't working.\n";
    }

    return 0;
}
