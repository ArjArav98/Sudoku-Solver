/* Copyright 2023 Arjun Aravind */

#include<iostream>
#include<fstream>
#include<array>
#include<set>
#include<algorithm>
#include<utility>
#include<stdexcept>

class SudokuGrid {
    private:
    std::array< std::array<int, 9> , 9> grid;
    std::set< std::pair<int, int> > coords_that_were_pre_filled;

    public:
    SudokuGrid() {
        std::array<int, 9> filled_array = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        grid.fill(filled_array);
    }

    void set(std::pair<int, int> coord, int value) {
        if (coord.first < 0 || coord.first > 8)
            throw std::invalid_argument(
                "Coordinates should be within range 0 <= x <= 8");
        if (coord.second < 0 || coord.second > 8)
            throw std::invalid_argument(
                "Coordinates should be within range 0 <= x <= 8");
        if (value < 1 || value > 9)
            throw std::invalid_argument(
                "Cell value should be in range 1 <= x <= 9");

        coords_that_were_pre_filled.insert(coord);
        grid[coord.first][coord.second] = value;
    }

    private:
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
                    if (grid.at(row_iter).at(col_iter) == currentValue)
                        return false;
                }
            }

            return true;
    }

    friend std::ostream& operator<< (std::ostream& out, SudokuGrid grid);
};

std::ostream& operator<< (std::ostream& out, SudokuGrid grid) {
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

int main() {
    SudokuGrid grid;
    grid.set(std::make_pair(0, 0), 3);
    grid.set(std::make_pair(8, 0), 7);
    std::cout << grid.value_exists_in_column(0, 7) << std::endl;
    std::cout << grid.value_exists_in_column(1, 7) << std::endl;
    return 0;
}
