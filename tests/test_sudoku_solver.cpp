/* Copyright 2023 Arjun Aravind */

#include<array>
#include<vector>
#include<algorithm>

#include"../src/sudoku_suite.h"

void test_value_exists_in_column() {
    /* We check functionality of the value_exists_in_column function. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }};

    sudoku::PuzzleGrid puzzle;
    puzzle.set(grid);

    assert(puzzle.value_exists_in_column(0,7) == true);
    assert(puzzle.value_exists_in_column(5,1) == false);
    assert(puzzle.value_exists_in_column(0,2) == false);
    assert(puzzle.value_exists_in_column(5,3) == true);
    assert(puzzle.value_exists_in_column(8,1) == false);
}

void test_value_exists_in_row() {
    /* We check functionality of the value_exists_in_row function. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }};

    sudoku::PuzzleGrid puzzle;
    puzzle.set(grid);

    assert(puzzle.value_exists_in_row(0,8) == true);
    assert(puzzle.value_exists_in_row(8,1) == false);
    assert(puzzle.value_exists_in_row(6,9) == true);
}

void test_value_exists_in_3x3_grid() {
    /* We check functionality of the value_exists_in_3x3_grid function. */
    std::array<std::array<int, 9>, 9> grid = {{
        {{ 0, 0, 0, 0, 0, 0, 6, 8, 0 }},
        {{ 0, 0, 0, 0, 7, 3, 0, 0, 9 }},
        {{ 3, 0, 9, 0, 0, 0, 0, 4, 5 }},
        {{ 4, 9, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 8, 0, 3, 0, 5, 0, 9, 0, 2 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 3, 6 }},
        {{ 9, 6, 0, 0, 0, 0, 3, 0, 8 }},
        {{ 7, 0, 0, 6, 8, 0, 0, 0, 0 }},
        {{ 0, 2, 8, 0, 0, 0, 0, 0, 0 }}
    }};

    sudoku::PuzzleGrid puzzle;
    puzzle.set(grid);

    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(2,2),3) == true);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(2,2),1) == false);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(5,4),5) == true);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(5,5),3) == false);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(8,8),7) == false);
    assert(puzzle.value_exists_in_3x3_grid(std::make_pair(6,6),7) == false);
}

int main() {
    auto tests = std::vector<void(*)()>{
        test_value_exists_in_column,
        test_value_exists_in_row,
        test_value_exists_in_3x3_grid
    };
    
    std::for_each(
        tests.begin(),
        tests.end(),
        [] (auto test) -> void {
            test();
            std::cout<<"Test executed successfully."<<std::endl;
        });

    return 0;
}
