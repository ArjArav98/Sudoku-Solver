/* Copyright 2023 Arjun Aravind */
#ifndef TESTS_TEST_GRID_H_
#define TESTS_TEST_GRID_H_

#include<utility>
#include<vector>

#include"../src/grid.h"

void test_puzzle_initial_state_is_set_correctly() {
    /* We check if the set_initial_state() function correctly
     * adds the non-'0' value coordinates to the list of coords
     * that were pre-filled. */
    sudoku::Grid grid({{
        {{ 0, 0, 3, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 1, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 7, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 9 }},
    }});

    assert(grid.coord_was_pre_filled(std::make_pair(0, 2)));
    assert(grid.coord_was_pre_filled(std::make_pair(8, 8)));
    assert(grid.coord_was_pre_filled(std::make_pair(4, 0)));
    assert(grid.coord_was_pre_filled(std::make_pair(5, 5)));
    assert(grid.coord_was_pre_filled(std::make_pair(6, 6)) == false);
}

void test_puzzle_initial_state_is_set_correctly_from_file() {
    /* We check if the set_initial_state_from_file() function correctly
     * loads the values from a file and sets the initial state. */

    sudoku::Grid grid_from_file;
    grid_from_file.set_initial_state_from_file("tests/test_data_1.txt");

    sudoku::Grid expected_output({{
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

    assert(grid_from_file == expected_output);
}

void test_puzzle_initial_state_isnt_set_due_to_incorrect_values() {
    /* We check if the set_initial_state_from_file() function errors out
     * when the values in the file are incorrect. */

    bool exception_not_thrown = true;
    sudoku::Grid grid_from_file;

    /*----------*/
    /* This file contains values which are >9. It should error out. */
    /*----------*/

    try {
        grid_from_file.set_initial_state_from_file("tests/test_data_2.txt");
    } catch (std::invalid_argument ia) {
        exception_not_thrown = false;
    }

    if (exception_not_thrown) assert(false);

    /*----------*/
    /* This file contains too many values. It should error out. */
    /*----------*/
    exception_not_thrown = true;

    try {
        grid_from_file.set_initial_state_from_file("tests/test_data_3.txt");
    } catch (std::invalid_argument ia) {
        exception_not_thrown = false;
    }

    if (exception_not_thrown) assert(false);

    /*----------*/
    /* This file contains too little values. It should error out. */
    /*----------*/
    exception_not_thrown = true;

    try {
        grid_from_file.set_initial_state_from_file("tests/test_data_4.txt");
    } catch (std::invalid_argument ia) {
        exception_not_thrown = false;
    }

    if (exception_not_thrown) assert(false);
}

void test_exception_is_thrown_if_file_doesnt_exist() {
    /* We check if the set_initial_state_from_file() function
     * throws an std::invalid_argument exception if the file doesn't exist. */

    bool exception_not_thrown = true;
    sudoku::Grid grid_from_file;

    try {
        grid_from_file.set_initial_state_from_file("some_random_thing.txt");
    } catch (std::invalid_argument ia) {
        exception_not_thrown = false;
    }

    if (exception_not_thrown) assert(false);
}

void test_value_exists_in_column() {
    /* We check functionality of the value_exists_in_column function. */
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

    assert(grid.value_exists_elsewhere_in_column(std::make_pair(0, 0),  7)
        == true);
    assert(grid.value_exists_elsewhere_in_column(std::make_pair(1, 5),  1)
        == false);
    assert(grid.value_exists_elsewhere_in_column(std::make_pair(2, 0),  2)
        == false);
    assert(grid.value_exists_elsewhere_in_column(std::make_pair(3, 5),  3)
        == true);
    assert(grid.value_exists_elsewhere_in_column(std::make_pair(4, 8),  1)
        == false);
    assert(grid.value_exists_elsewhere_in_column(std::make_pair(7, 0),  7)
        == false);  // The coord itself shouldn't be checked.
}

void test_value_exists_in_row() {
    /* We check functionality of the value_exists_in_row function. */
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

    assert(grid.value_exists_elsewhere_in_row(std::make_pair(0, 0), 8)
        == true);
    assert(grid.value_exists_elsewhere_in_row(std::make_pair(6, 1), 9)
        == true);
    assert(grid.value_exists_elsewhere_in_row(std::make_pair(8, 0), 1)
        == false);
    assert(grid.value_exists_elsewhere_in_row(std::make_pair(1, 8), 9)
        == false);  // The coord itself shouldn't be checked.
}

void test_value_exists_in_3x3_grid() {
    /* We check functionality of the value_exists_in_3x3_grid function. */
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

    assert(grid.value_exists_elsewhere_in_3x3_grid(std::make_pair(2, 2), 3)
        == true);
    assert(grid.value_exists_elsewhere_in_3x3_grid(std::make_pair(2, 2), 1)
        == false);
    assert(grid.value_exists_elsewhere_in_3x3_grid(std::make_pair(5, 4), 5)
        == true);
    assert(grid.value_exists_elsewhere_in_3x3_grid(std::make_pair(5, 5), 3)
        == false);
    assert(grid.value_exists_elsewhere_in_3x3_grid(std::make_pair(8, 8), 7)
        == false);
    assert(grid.value_exists_elsewhere_in_3x3_grid(std::make_pair(6, 6), 7)
        == false);
    assert(grid.value_exists_elsewhere_in_3x3_grid(std::make_pair(7, 0), 7)
        == false);  // The coord itself shouldn't be checked.
}

void test_possible_cell_values_generated_correctly() {
    /* We check if the get_possible_values_for_cell_at_coord()
     * function generates the possible values for each cell correctly. */
    sudoku::Grid puzzle({{
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

    auto obtained_value = puzzle.get_possible_values_for_cell_at_coord(
        std::make_pair(0, 0));
    auto expected_value = std::vector<int>{ 1, 2, 5 };
    assert(obtained_value == expected_value);

    obtained_value = puzzle.get_possible_values_for_cell_at_coord(
        std::make_pair(5, 6));
    expected_value = std::vector<int>{ 1, 4, 5, 7, 8 };
    assert(obtained_value == expected_value);

    obtained_value = puzzle.get_possible_values_for_cell_at_coord(
        std::make_pair(8, 8));
    expected_value = std::vector<int>{ 1, 4, 7 };
    assert(obtained_value == expected_value);
}

#endif  // TESTS_TEST_GRID_H_
