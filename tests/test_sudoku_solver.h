/* Copyright 2023 Arjun Aravind */
#ifndef TESTS_TEST_SUDOKU_SOLVER_H_
#define TESTS_TEST_SUDOKU_SOLVER_H_

#include"../src/sudoku_solver.h"

void test_puzzle_is_solved_correctly() {
    /* We check if the solve() function correctly solves the puzzle given. */
    sudoku::Grid unsolved_puzzle_grid({{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 7 }}
    }});

    sudoku::solve(&unsolved_puzzle_grid);

    sudoku::Grid expected_answer_grid({{
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

    assert(unsolved_puzzle_grid == expected_answer_grid);

    /*====TEST 2====*/

    unsolved_puzzle_grid.set_initial_state({{
        {{ 9, 7, 8, 4, 1, 0, 0, 0, 5 }},
        {{ 3, 0, 0, 8, 0, 0, 0, 6, 4 }},
        {{ 6, 0, 0, 3, 5, 0, 0, 9, 0 }},
        {{ 2, 6, 9, 0, 3, 0, 0, 0, 7 }},
        {{ 5, 0, 7, 1, 0, 0, 0, 0, 0 }},
        {{ 1, 0, 3, 0, 0, 2, 0, 8, 9 }},
        {{ 7, 1, 0, 2, 0, 5, 0, 0, 3 }},
        {{ 0, 0, 2, 7, 0, 3, 1, 5, 8 }},
        {{ 0, 0, 5, 9, 4, 1, 0, 0, 0 }}
    }});

    sudoku::solve(&unsolved_puzzle_grid);

    expected_answer_grid.set_initial_state({{
        {{ 9, 7, 8, 4, 1, 6, 2, 3, 5 }},
        {{ 3, 5, 1, 8, 2, 9, 7, 6, 4 }},
        {{ 6, 2, 4, 3, 5, 7, 8, 9, 1 }},
        {{ 2, 6, 9, 5, 3, 8, 4, 1, 7 }},
        {{ 5, 8, 7, 1, 9, 4, 3, 2, 6 }},
        {{ 1, 4, 3, 6, 7, 2, 5, 8, 9 }},
        {{ 7, 1, 6, 2, 8, 5, 9, 4, 3 }},
        {{ 4, 9, 2, 7, 6, 3, 1, 5, 8 }},
        {{ 8, 3, 5, 9, 4, 1, 6, 7, 2 }}
    }});

    assert(unsolved_puzzle_grid == expected_answer_grid);
}

#endif  // TESTS_TEST_SUDOKU_SOLVER_H_
