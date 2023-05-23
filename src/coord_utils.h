/* Copyright 2023 Arjun Aravind */
#ifndef SRC_COORD_UTILS_H_
#define SRC_COORD_UTILS_H_

#include<chrono>
#include<random>
#include<set>
#include<utility>
#include<vector>

#include"../src/coord.h"

namespace sudoku {

Coord get_next_cell_coord(Coord coord) {
    /* Function which returns the next successive coordinate for a
     * Sudoku grid, given a current coordinate. */
    if (coord.second == GRID_LEN-1 && coord.first == GRID_LEN-1)
        return coord;
    else if (coord.second == GRID_LEN-1)
        return std::make_pair(coord.first+1, 0);
    return std::make_pair(coord.first, coord.second + 1);
}

std::set<Coord> get_N_random_cell_coords(int n) {
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd());  // seed the generator
    std::uniform_int_distribution<> distr(0, GRID_LEN-1);  // define the range

    std::set<Coord> random_cell_coords;

    while (n > 0) {
        auto cell_coord = std::make_pair(distr(gen), distr(gen));
        auto inserted = random_cell_coords.insert(cell_coord);

        if (!inserted.second) continue;  // Element already existed.
        n--;
    }

    return random_cell_coords;
}

}  // namespace sudoku

#endif  // SRC_COORD_UTILS_H_
