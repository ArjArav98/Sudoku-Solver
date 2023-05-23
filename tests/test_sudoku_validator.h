/* Copyright 2023 Arjun Aravind */
#ifndef TESTS_TEST_SUDOKU_VALIDATOR_H_
#define TESTS_TEST_SUDOKU_VALIDATOR_H_

#include"../src/sudoku_validator.h"

void test_validator_validates_grids_as_expected() {
    /* We check if the is_valid_solution() function
     * validates the given solutions as expected. */
    sudoku::Grid valid_solution({{
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

    sudoku::Grid unfinished_solution({{
        {{ 9, 7, 8, 4, 1, 6, 2, 3, 0 }},
        {{ 3, 5, 1, 8, 2, 9, 7, 6, 0 }},
        {{ 6, 2, 4, 3, 5, 7, 8, 9, 0 }},
        {{ 2, 6, 9, 5, 3, 8, 4, 1, 0 }},
        {{ 5, 8, 7, 1, 9, 4, 3, 2, 0 }},
        {{ 1, 4, 3, 6, 7, 2, 5, 8, 0 }},
        {{ 7, 1, 6, 2, 8, 5, 9, 4, 0 }},
        {{ 4, 9, 2, 7, 6, 3, 1, 5, 0 }},
        {{ 8, 3, 5, 9, 4, 1, 6, 7, 0 }}
    }});

    sudoku::Grid invalid_solution({{
        {{ 9, 7, 8, 4, 1, 6, 2, 3, 5 }},
        {{ 3, 5, 1, 8, 2, 9, 7, 6, 4 }},
        {{ 6, 2, 4, 3, 5, 7, 8, 9, 1 }},
        {{ 2, 6, 9, 5, 3, 8, 4, 1, 7 }},
        {{ 5, 8, 7, 1, 9, 4, 3, 2, 6 }},
        {{ 1, 4, 3, 6, 7, 2, 5, 8, 9 }},
        {{ 7, 1, 6, 2, 8, 5, 9, 4, 3 }},
        {{ 4, 9, 2, 7, 6, 3, 1, 5, 8 }},
        {{ 8, 3, 5, 9, 4, 1, 5, 5, 5 }}  // 5 appears 4x
    }});

    assert(sudoku::is_valid_solution(valid_solution) == true);
    assert(sudoku::is_valid_solution(unfinished_solution) == false);
    assert(sudoku::is_valid_solution(invalid_solution) == false);
}

#endif  // TESTS_TEST_SUDOKU_VALIDATOR_H_
