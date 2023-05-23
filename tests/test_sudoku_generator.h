/* Copyright 2023 Arjun Aravind */
#ifndef TESTS_TEST_SUDOKU_GENERATOR_H_
#define TESTS_TEST_SUDOKU_GENERATOR_H_

#include"../src/sudoku_generator.h"

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

#endif  // TESTS_TEST_SUDOKU_GENERATOR_H_
