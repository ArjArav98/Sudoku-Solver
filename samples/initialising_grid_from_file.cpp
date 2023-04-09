/* A basic example. */

#include<iostream>
#include"../src/sudoku_suite.h"

int main() {
    sudoku::Grid grid;
    grid.set_initial_state_from_file("samples/sample1.txt");
    std::cout << grid << std::endl;

    sudoku::solve(&grid);
    std::cout << grid << std::endl;

    return 0;
}
