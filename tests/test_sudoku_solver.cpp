/* Copyright 2023 Arjun Aravind */

#include<array>
#include<vector>
#include<algorithm>

#include"../src/sudoku_suite.h"

void test_puzzle_initial_state_is_set_correctly() {
    /* We check if the set_initial_state() function correctly
     * adds the non-'0' value coordinates to the list of coords
     * that were pre-filled. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 3, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 1, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 7, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 9 }},
    }};

    sudoku::PuzzleGrid puzzle(grid);

    assert(puzzle.coord_was_pre_filled(std::make_pair(0,2)));
    assert(puzzle.coord_was_pre_filled(std::make_pair(8,8)));
    assert(puzzle.coord_was_pre_filled(std::make_pair(4,0)));
    assert(puzzle.coord_was_pre_filled(std::make_pair(5,5)));
    assert(puzzle.coord_was_pre_filled(std::make_pair(6,6)) == false);
}

void test_value_exists_in_column() {
    /* We check functionality of the value_exists_in_column function. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }};

    sudoku::PuzzleGrid puzzle(grid);

    assert(puzzle.value_exists_in_column(0, 7) == true);
    assert(puzzle.value_exists_in_column(5, 1) == false);
    assert(puzzle.value_exists_in_column(0, 2) == false);
    assert(puzzle.value_exists_in_column(5, 3) == true);
    assert(puzzle.value_exists_in_column(8, 1) == false);
}

void test_value_exists_in_row() {
    /* We check functionality of the value_exists_in_row function. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }};

    sudoku::PuzzleGrid puzzle(grid);

    assert(puzzle.value_exists_in_row(0, 8) == true);
    assert(puzzle.value_exists_in_row(8, 1) == false);
    assert(puzzle.value_exists_in_row(6, 9) == true);
}

void test_value_exists_in_3x3_grid() {
    /* We check functionality of the value_exists_in_3x3_grid function. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }};

    sudoku::PuzzleGrid puzzle(grid);

    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(2, 2), 3) == true);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(2, 2), 1) == false);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(5, 4), 5) == true);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(5, 5), 3) == false);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(8, 8), 7) == false);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(6, 6), 7) == false);
}

void test_possible_cell_values_generated_correctly() {
    /* We check if the get_possible_values_for_cell_at_coord()
     * function generates the possible values for each cell correctly. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }};

    sudoku::PuzzleGrid puzzle(grid);

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

int main() {
    auto tests = std::vector<void(*)()>{
        test_puzzle_initial_state_is_set_correctly,
        test_value_exists_in_column,
        test_value_exists_in_row,
        test_value_exists_in_3x3_grid,
        test_possible_cell_values_generated_correctly,
        test_successive_cell_coords_are_generated_correctly
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
