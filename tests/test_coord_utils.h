/* Copyright 2023 Arjun Aravind */
#ifndef TESTS_TEST_COORD_UTILS_H_
#define TESTS_TEST_COORD_UTILS_H_

#include<utility>

#include"../src/coord_utils.h"

void test_successive_cell_coords_are_generated_correctly() {
    /* We test that the get_next_cell_coord() function correctly
     * generates the next successive coord value for the sudoku grid. */
    assert(
        sudoku::get_next_cell_coord(std::make_pair(0, 0))
        == std::make_pair(0, 1));

    assert(
        sudoku::get_next_cell_coord(std::make_pair(0, 8))
        == std::make_pair(1, 0));

    assert(
        sudoku::get_next_cell_coord(std::make_pair(8, 8))
        == std::make_pair(8, 8));
}

#endif  // TESTS_TEST_COORD_UTILS_H_
