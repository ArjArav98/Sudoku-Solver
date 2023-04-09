/* A basic example. */

#include<iostream>
#include"../src/sudoku_suite.h"

int main() {
    sudoku::Grid grid = sudoku::generate_puzzle();
    std::cout << grid << std::endl;

    return 0;
}
