/* Copyright 2023 Arjun Aravind */

#include"../tests/test_grid.h"
#include"../tests/test_coord_utils.h"
#include"../tests/test_sudoku_solver.h"
#include"../tests/test_sudoku_validator.h"
#include"../tests/test_sudoku_generator.h"

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
