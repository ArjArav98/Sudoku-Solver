/* Copyright 2023 Arjun Aravind */
#ifndef SRC_SUDOKU_SUITE_H_
#define SRC_SUDOKU_SUITE_H_
#endif  // SRC_SUDOKU_SUITE_H_

#include<iostream>
#include<fstream>
#include<array>
#include<set>
#include<vector>
#include<algorithm>
#include<utility>
#include<stdexcept>


namespace sudoku {

class PuzzleGrid {
    private:
    std::array<std::array<int, 9>, 9> grid;
    std::set< std::pair<int, int> > coords_that_were_pre_filled;

    public:
    PuzzleGrid() {
        std::array<int, 9> filled_array = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        grid.fill(filled_array);
    }

    explicit PuzzleGrid(std::array<std::array<int, 9>, 9> grid) {
        set_initial_state(grid);
    }

    void set_initial_state(std::array<std::array<int, 9>, 9> grid) {
        /* A function that lets us set the initial state of the puzzle.
         * '0' values represent empty cells and values between '1' and '9'
         * represent pre-filled values. Any other value results in error. */
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                int cell_value = grid.at(row).at(col);

                if (cell_value < 0 || cell_value > 9) {
                    throw std::invalid_argument(
                        "Cell value should be in range 0 <= x <= 9");
                }

                this->grid.at(row).at(col) = cell_value;
                if (cell_value == 0) continue;
                coords_that_were_pre_filled.insert(std::make_pair(row, col));
            }
        }
    }

    int get(std::pair<int, int> coord) {
        return grid.at(coord.first).at(coord.second);
    }

    void clear_values_starting_from_coord(std::pair<int, int> coord) {
        for (int row = coord.first; row < 9; row++) {
            for (int col = coord.second; col < 9; col++) {
                auto pos_in_pre_filled = std::find(
                    coords_that_were_pre_filled.begin(),
                    coords_that_were_pre_filled.end(),
                    coord);
                if (pos_in_pre_filled == coords_that_were_pre_filled.end()) {
                    grid.at(coord.first).at(coord.second) = 0;
                }
            }
        }
    }

    bool value_exists_in_column(int column_index, int value) {
        return std::any_of(
            grid.begin(),
            grid.end(),
            [=] (std::array<int, 9> grid_row) -> bool {
                return grid_row.at(column_index) == value;
            });
    }

    bool value_exists_in_row(int row_index, int value) {
        return std::any_of(
            grid.at(row_index).begin(),
            grid.at(row_index).end(),
            [=] (int cell) -> bool {
                return cell == value;
            });
    }

    bool value_exists_in_3x3_grid(std::pair<int, int> coord, int value) {
        int row_start = (coord.first/3)*3;
        int row_end = (row_start+2);

        int col_start = (coord.second/3)*3;
        int col_end = (col_start+2);

        for (int row_iter=row_start; row_iter <= row_end; row_iter++) {
            for (int col_iter = col_start; col_iter <= col_end; col_iter++) {
                if (grid.at(row_iter).at(col_iter) == value)
                    return true;
            }
        }

        return false;
    }

    bool coord_was_pre_filled(std::pair<int, int> coord) {
        auto element_found = std::find(
            coords_that_were_pre_filled.begin(),
            coords_that_were_pre_filled.end(),
            coord);

        return (element_found != coords_that_were_pre_filled.end());
    }

    friend std::ostream& operator<< (std::ostream& out, PuzzleGrid grid);
};

std::ostream& operator<< (std::ostream& out, PuzzleGrid grid) {
    out << "+-------+-------+-------+\n";
    for (int row_index=0; row_index < 9; row_index++) {
        out << "|";
        for (int col_index=0; col_index < 9; col_index++) {
            out << " " << grid.grid[row_index][col_index];
            if (col_index%3 == 2) out << " |";
        }
        out << "\n";
        if (row_index%3 == 2) out << "+-------+-------+-------+\n";
    }
    return out;
}

std::pair<int, int> get_next_cell_coord(std::pair<int, int> coord) {
    if (coord.second == 8 && coord.first == 8) return coord;
    else if (coord.second == 8) return std::make_pair(coord.first + 1, 0);
    return std::make_pair(coord.first, coord.second + 1);
}

std::vector<int> get_possible_values_for_cell_at_coord(
    PuzzleGrid *puzzle,
    std::pair<int, int> coord
) {
    std::vector<int> values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> filtered_values(values.size());

    auto it = std::copy_if(
        values.begin(), values.end(),
        filtered_values.begin(),
        [&puzzle, coord] (int value) -> bool {
            return !(
                puzzle.value_exists_in_row(coord.first, value) ||
                puzzle.value_exists_in_column(coord.second, value) ||
                puzzle.value_exists_in_3x3_grid(coord, value));
        });

    // Shrink vector to remove empty elements.
    filtered_values.resize(std::distance(filtered_values.begin(), it));
    return filtered_values;
}

bool solved_for_cell_at_coord(
    PuzzleGrid *grid, std::pair<int, int> cell_coord
) {
    auto next_coord = get_next_cell_coord(cell_coord);

    if (grid->coord_was_pre_filled(cell_coord))
        return solved_for_cell_at_coord(next_coord);

    auto possible_values = get_possible_values_for_cell_at_coord(cell_coord);
    if (possible_values.size() == 0) return false;

    for (int value = 0; value
}

}  // namespace sudoku
