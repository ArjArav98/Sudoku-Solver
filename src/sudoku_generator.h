/* Copyright 2023 Arjun Aravind */
#ifndef SRC_SUDOKU_GENERATOR_H_
#define SRC_SUDOKU_GENERATOR_H_

#include<chrono>
#include<random>
#include<utility>

#include"../src/grid.h"
#include"../src/coord_utils.h"

namespace sudoku {

bool fill_with_valid_solution(
    Grid *grid,
    Coord curr_coord = std::make_pair(0, 0)
) {
    auto next_coord = get_next_cell_coord(curr_coord);

    auto values = grid->get_possible_values_for_cell_at_coord(curr_coord);
    if (values.size() == 0) return false;

    // We randomise the values so that we get a random solution each time.
    auto rnd_seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(
        values.begin(),
        values.end(),
        std::default_random_engine(rnd_seed));

    for (auto value : values) {
        grid->update(curr_coord, value);
        if (curr_coord == std::make_pair(8, 8)) return true;  // Done

        bool next_cell_is_filled = fill_with_valid_solution(grid, next_coord);
        if (next_cell_is_filled) return true;

        /* If this value didn't work, we need to clear the grid of all the
         * values that have been filled as a result of this. */
        grid->clear_values_starting_from_coord(curr_coord);
    }

    return false;
}

void remove_values_from_solution(Grid *grid, int values_to_remove) {
    auto random_cell_coords = get_N_random_cell_coords(values_to_remove);
    for (auto coord : random_cell_coords) grid->update(coord, 0);
}

Grid generate_puzzle() {
    Grid grid;
    fill_with_valid_solution(&grid);
    remove_values_from_solution(&grid, 30);
    return grid;
}

}  // namespace sudoku

#endif  // SRC_SUDOKU_GENERATOR_H_
