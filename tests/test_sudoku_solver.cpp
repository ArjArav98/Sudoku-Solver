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

    assert(grid.value_exists_in_column(std::make_pair(0, 0),  7) == true);
    assert(grid.value_exists_in_column(std::make_pair(1, 5),  1) == false);
    assert(grid.value_exists_in_column(std::make_pair(2, 0),  2) == false);
    assert(grid.value_exists_in_column(std::make_pair(3, 5),  3) == true);
    assert(grid.value_exists_in_column(std::make_pair(4, 8),  1) == false);
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

    assert(grid.value_exists_in_row(std::make_pair(0, 0), 8) == true);
    assert(grid.value_exists_in_row(std::make_pair(8, 0), 1) == false);
    assert(grid.value_exists_in_row(std::make_pair(6, 0), 9) == true);
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

    assert(grid.value_exists_in_3x3_grid(std::make_pair(2, 2), 3) == true);
    assert(grid.value_exists_in_3x3_grid(std::make_pair(2, 2), 1) == false);
    assert(grid.value_exists_in_3x3_grid(std::make_pair(5, 4), 5) == true);
    assert(grid.value_exists_in_3x3_grid(std::make_pair(5, 5), 3) == false);
    assert(grid.value_exists_in_3x3_grid(std::make_pair(8, 8), 7) == false);
    assert(grid.value_exists_in_3x3_grid(std::make_pair(6, 6), 7) == false);
}

void test_possible_cell_values_generated_correctly() {
    /* We check if the get_values_for_cell_at_coord()
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

    auto obtained_value = sudoku::get_values_for_cell_at_coord(
        puzzle, std::make_pair(0, 0));
    auto expected_value = std::vector<int>{ 1, 2, 5 };
    assert(obtained_value == expected_value);

    obtained_value = sudoku::get_values_for_cell_at_coord(
        puzzle, std::make_pair(5, 6));
    expected_value = std::vector<int>{ 1, 4, 5, 7, 8 };
    assert(obtained_value == expected_value);

    obtained_value = sudoku::get_values_for_cell_at_coord(
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
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
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

int main() {
    auto tests = std::vector<void(*)()>{
        test_puzzle_initial_state_is_set_correctly,
        test_value_exists_in_column,
        test_value_exists_in_row,
        test_value_exists_in_3x3_grid,
        test_possible_cell_values_generated_correctly,
        test_successive_cell_coords_are_generated_correctly,
        test_puzzle_is_solved_correctly
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
