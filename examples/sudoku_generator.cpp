/* Copyright 2023 Arjun Aravind */
/* A basic example as seen in the project's README. */

#include<iostream>
#include"../src/sudoku_generator.h"

int main() {
    sudoku::Grid grid = sudoku::generate_puzzle();
    std::cout << grid << std::endl;

    return 0;
}
