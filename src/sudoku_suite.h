/* Copyright 2023 Arjun Aravind */

#include<iostream>
#include<fstream>
#include<array>
#include<set>
#include<vector>
#include<algorithm>
#include<utility>
#include<stdexcept>

namespace sudoku {
    class PuzzleGrid;

    std::ostream& operator<< (std::ostream& out, PuzzleGrid grid);
    std::vector<int> get_possible_values_for_cell_at_coord(
        PuzzleGrid puzzle,
        std::pair<int, int> coord
    );
}

class sudoku::PuzzleGrid {
    private:
    std::array<std::array<int, 9>, 9> grid;
    std::set< std::pair<int, int> > coords_that_were_pre_filled;

    public:
    PuzzleGrid() {
        std::array<int, 9> filled_array = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        grid.fill(filled_array);
    }

    void set(std::pair<int, int> coord, int value) {
        /* set() variant that lets us set the puzzle one cell
         * at a time.
         * Note: A cell with a value '0' represents that it is
         * currently empty. */
        if (coord.first < 0 || coord.first > 8)
            throw std::invalid_argument(
                "Row coords should be within range 0 <= x <= 8");
        if (coord.second < 0 || coord.second > 8)
            throw std::invalid_argument(
                "Column coords should be within range 0 <= x <= 8");
        if (value < 0 || value > 9)
            throw std::invalid_argument(
                "Cell value should be in range 0 <= x <= 9");

        coords_that_were_pre_filled.insert(coord);
        grid[coord.first][coord.second] = value;
    }

    void set(std::array<std::array<int, 9>, 9> grid) {
        /* set() variant that lets us set the puzzle by
         * passing the entire 2D grid at once.
         * Note: A cell with a value '0' represents that it is
         * currently empty. */
        auto invalid = std::any_of(
            grid.begin(),
            grid.end(),
            [] (std::array<int, 9> grid_row) -> bool {
                return std::any_of(
                    grid_row.begin(),
                    grid_row.end(),
                    [] (int value) -> bool {
                        return (value < 0 || value > 9);
                    });
            });

        if (invalid) throw std::invalid_argument(
            "Cell value should be in range 0 <= x <= 9");

        this->grid = grid;
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

    friend std::ostream& operator<< (std::ostream& out, PuzzleGrid grid);
};

std::ostream& sudoku::operator<< (std::ostream& out, PuzzleGrid grid) {
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

std::vector<int> sudoku::get_possible_values_for_cell_at_coord(
    PuzzleGrid puzzle,
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
