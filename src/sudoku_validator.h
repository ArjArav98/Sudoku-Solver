/* Copyright 2023 Arjun Aravind */
#ifndef SRC_SUDOKU_VALIDATOR_H_
#define SRC_SUDOKU_VALIDATOR_H_

#include<utility>

#include"../src/grid.h"
#include"../src/coord_utils.h"

namespace sudoku {

bool is_valid_solution(
    const Grid& grid,
    Coord curr_coord = std::make_pair(0, 0)
) {
    int value = grid.get(curr_coord);
    if (value == 0) return false;  // It's unfinished.
    else if (
        grid.value_exists_elsewhere_in_column(curr_coord, value) ||
        grid.value_exists_elsewhere_in_row(curr_coord, value) ||
        grid.value_exists_elsewhere_in_3x3_grid(curr_coord, value))
        return false;
    if (curr_coord == std::make_pair(8, 8)) return true;
    else
        return is_valid_solution(grid, get_next_cell_coord(curr_coord));
}

}  // namespace sudoku

#endif  // SRC_SUDOKU_VALIDATOR_H_
