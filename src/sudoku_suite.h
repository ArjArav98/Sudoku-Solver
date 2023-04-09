/* Copyright 2023 Arjun Aravind */
#ifndef SRC_SUDOKU_SUITE_H_
#define SRC_SUDOKU_SUITE_H_
#endif  // SRC_SUDOKU_SUITE_H_

#include<iostream>
#include<fstream>
#include<array>
#include<set>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<stdexcept>
#include<chrono>
#include<random>

namespace sudoku {

typedef std::pair<int, int> Coord;

int GRID_LEN = 9;

class Grid {
    /* A data structure that holds the Sudoku puzzle. */
    private:
    std::array<std::array<int, 9>, 9> grid;
    std::set<Coord> coords_that_were_pre_filled;

    public:
    Grid() {
        std::array<int, 9> filled_array = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        grid.fill(filled_array);
    }

    explicit Grid(std::array<std::array<int, 9>, 9> grid) {
        set_initial_state(grid);
    }

    /*---------------------*/
    /* Setters and Getters */

    void set_initial_state(std::array<std::array<int, 9>, 9> grid) {
        /* A function that lets us set the initial state of the puzzle.
         * '0' values represent empty cells and values between '1' and '9'
         * represent pre-filled values. Any other value results in error. */
        coords_that_were_pre_filled.clear();

        for (int row = 0; row < GRID_LEN; row++) {
            for (int col = 0; col < GRID_LEN; col++) {
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

    void set_initial_state_from_file(std::string filename) {
        /* A wrapper around the set_initial_state() function
         * so that we can set the initial state from a file.
         *
         * The set_initial_state() function contains useful logic
         * relating to the input which we are reusing. */
        std::ifstream file;
        file.open(filename, std::ios::in);
        if (file.fail()) throw std::invalid_argument(
            "The file couldn't be opened. Please check if the file exists.");

        std::array<std::array<int, 9>, 9> grid;

        for (int row_index = 0; row_index < GRID_LEN; row_index++) {
            for (int col_index = 0; col_index < GRID_LEN; col_index++) {
                file >> grid.at(row_index).at(col_index);
                if (file.eof()) throw std::invalid_argument(
                    "Too little values provided. Please supply 81 values.");
            }
        }

        int value;
        file >> value;
        if (!file.eof()) throw std::invalid_argument(
            "Too many values provided. Please supply only 81 values.");

        file.close();
        set_initial_state(grid);
    }

    void update(Coord coord, int value) {
        if (value < 0 || value > 9) throw std::invalid_argument(
            "Cell value should be in range 0 <= x <= 9");
        grid.at(coord.first).at(coord.second) = value;
    }

    int get(Coord coord) const {
        return grid.at(coord.first).at(coord.second);
    }

    void clear_values_starting_from_coord(Coord coord) {
        for (int row = coord.first; row < GRID_LEN; row++) {
            for (int col = coord.second; col < GRID_LEN; col++) {
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

    /*----------*/
    /* Checkers */

    bool value_exists_elsewhere_in_column(Coord coord, int value) const {
        int row_index = -1;

        return std::any_of(
            grid.begin(),
            grid.end(),
            [=, &row_index] (std::array<int, 9> grid_row) -> bool {
                // The coord itself doesn't count.
                bool row_diff_to_coord_row = (coord.first != ++row_index);
                return
                    (grid_row.at(coord.second) == value) &&
                    row_diff_to_coord_row;
            });
    }

    bool value_exists_elsewhere_in_row(Coord coord, int value) const {
        int col_index = -1;

        return std::any_of(
            grid.at(coord.first).begin(),
            grid.at(coord.first).end(),
            [=, &col_index] (int cell) -> bool {
                // The coord itself doesn't count.
                bool col_diff_to_coord_col = (coord.second != ++col_index);
                return (cell == value) && col_diff_to_coord_col;
            });
    }

    bool value_exists_elsewhere_in_3x3_grid(Coord coord, int value) const {
        int row_start = (coord.first/3)*3;
        int row_end = (row_start+2);

        int col_start = (coord.second/3)*3;
        int col_end = (col_start+2);

        for (int row_iter=row_start; row_iter <= row_end; row_iter++) {
            for (int col_iter = col_start; col_iter <= col_end; col_iter++) {
                // The coord itself doesn't count.
                bool coord_diff_to_given_coord =
                    std::make_pair(row_iter, col_iter) != coord;
                if (coord_diff_to_given_coord &&
                    (grid.at(row_iter).at(col_iter) == value)) return true;
            }
        }

        return false;
    }

    bool coord_was_pre_filled(Coord coord) const {
        auto element_found = std::find(
            coords_that_were_pre_filled.begin(),
            coords_that_were_pre_filled.end(),
            coord);

        return (element_found != coords_that_were_pre_filled.end());
    }

    /*--------------------*/
    /* Operator Overloads */

    bool operator== (const Grid& grid) const {
        for (int row = 0; row < GRID_LEN; row++) {
            for (int col = 0; col < GRID_LEN; col++) {
                auto coord = std::make_pair(row, col);
                if (get(coord) != grid.get(coord)) return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<< (std::ostream& out, Grid grid);
};

std::ostream& operator<< (std::ostream& out, Grid grid) {
    out << "+-------+-------+-------+\n";
    for (int row_index=0; row_index < GRID_LEN; row_index++) {
        out << "|";
        for (int col_index=0; col_index < GRID_LEN; col_index++) {
            out << " " << grid.grid[row_index][col_index];
            if (col_index%3 == 2) out << " |";
        }
        out << "\n";
        if (row_index%3 == 2) out << "+-------+-------+-------+\n";
    }
    return out;
}

/*------------------*/
/* COORD FUNCTIONS  */
/*------------------*/

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

std::vector<int> get_possible_values_for_cell_at_coord(
    const Grid& grid,
    Coord coord
) {
    std::vector<int> values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<int> filtered_values(values.size());

    auto it = std::copy_if(
        values.begin(), values.end(),
        filtered_values.begin(),
        [&grid, coord] (int value) -> bool {
            return !(
                grid.value_exists_elsewhere_in_column(coord, value) ||
                grid.value_exists_elsewhere_in_row(coord, value) ||
                grid.value_exists_elsewhere_in_3x3_grid(coord, value));
        });

    // Shrink vector to remove empty elements.
    filtered_values.resize(std::distance(filtered_values.begin(), it));
    return filtered_values;
}

/*----------------------*/
/* GENERATION FUNCTIONS */
/*----------------------*/


bool fill_with_valid_solution(
    Grid *grid,
    Coord curr_coord = std::make_pair(0, 0)
) {
    auto next_coord = get_next_cell_coord(curr_coord);

    auto values = get_possible_values_for_cell_at_coord(*grid, curr_coord);
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

/*-----------------*/
/* SOLVE FUNCTIONS */
/*-----------------*/

bool _solve(
    Grid *grid,
    Coord cell_coord = std::make_pair(0, 0)
) {
    auto next_coord = get_next_cell_coord(cell_coord);

    if (grid->coord_was_pre_filled(cell_coord)) {
        if (cell_coord == std::make_pair(8, 8)) return true;
        return _solve(grid, next_coord);
    }

    auto values = get_possible_values_for_cell_at_coord(*grid, cell_coord);
    if (values.size() == 0) return false;

    for (auto value : values) {
        grid->update(cell_coord, value);
        if (cell_coord == std::make_pair(8, 8)) return true;  // Solved!

        bool next_cell_is_solved = _solve(grid, next_coord);
        if (next_cell_is_solved) return true;

        /* If this value didn't work, we need to clear the grid of all the
         * values that have been filled as a result of this. */
        grid->clear_values_starting_from_coord(cell_coord);
    }

    if (cell_coord == std::make_pair(0, 0)) throw std::logic_error(
        "This puzzle doesn't have a solution!");

    return false;
}

/*-----------------*/
/* SUITE FUNCTIONS */
/*-----------------*/

void solve(Grid *grid) {
    _solve(grid);
}

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

Grid generate_puzzle() {
    Grid grid;
    fill_with_valid_solution(&grid);
    remove_values_from_solution(&grid, 30);
    return grid;
}

}  // namespace sudoku
