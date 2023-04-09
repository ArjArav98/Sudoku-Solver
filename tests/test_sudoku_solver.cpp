/* Copyright 2023 Arjun Aravind */

#include<array>
#include<vector>
#include<algorithm>

#include"../src/sudoku_suite.h"

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

    auto obtained_value = sudoku::get_possible_values_for_cell_at_coord(
        puzzle, std::make_pair(0, 0));
    auto expected_value = std::vector<int>{ 1, 2, 5 };
    assert(obtained_value == expected_value);

    obtained_value = sudoku::get_possible_values_for_cell_at_coord(
        puzzle, std::make_pair(5, 6));
    expected_value = std::vector<int>{ 1, 4, 5, 7, 8 };
    assert(obtained_value == expected_value);

    obtained_value = sudoku::get_possible_values_for_cell_at_coord(
        puzzle, std::make_pair(8, 8));
    expected_value = std::vector<int>{ 1, 4, 7 };
    assert(obtained_value == expected_value);
}

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

void test_puzzle_generated_is_solvable() {
    /* We test if the generate_puzzle() function generates a puzzle
     * that CAN be solved. */
    auto generated_puzzle = sudoku::generate_puzzle();
    solve(&generated_puzzle);

    assert(is_valid_solution(generated_puzzle) == true);
}

void test_no_two_successive_puzzles_generated_are_same() {
    /* We test that no two successively generated puzzles, by the
     * generate_puzzle() function, are the same. */
    auto first_generated_puzzle = sudoku::generate_puzzle();
    auto second_generated_puzzle = sudoku::generate_puzzle();

    assert((first_generated_puzzle == second_generated_puzzle) == false);
}

int main() {
    auto tests = std::vector<void(*)()>{
        test_puzzle_initial_state_is_set_correctly,
        test_puzzle_initial_state_is_set_correctly_from_file,
        test_puzzle_initial_state_isnt_set_due_to_incorrect_values,
        test_exception_is_thrown_if_file_doesnt_exist,
        test_value_exists_in_column,
        test_value_exists_in_row,
        test_value_exists_in_3x3_grid,
        test_possible_cell_values_generated_correctly,
        test_successive_cell_coords_are_generated_correctly,
        test_puzzle_is_solved_correctly,
        test_validator_validates_grids_as_expected,
        test_puzzle_generated_is_solvable,
        test_no_two_successive_puzzles_generated_are_same
    };

    std::for_each(
        tests.begin(),
        tests.end(),
        [] (auto test) -> void {
            test();
            std::cout << "Test executed successfully." << std::endl;
        });

    return 0;
}
