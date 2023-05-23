/* Copyright 2023 Arjun Aravind */
/* A basic example as seen in the project's README. */

#include<iostream>
#include"../src/grid.h"

/* NOTE: If you only need to utilise the Grid object,
 * you can just import the "grid.h" header alone. */

int main() {
    sudoku::Grid sample_grid_1({{
        {{ 1, 7, 2, 5, 4, 9, 6, 8, 3 }},
        {{ 6, 4, 5, 8, 7, 3, 2, 1, 9 }},
        {{ 3, 8, 9, 2, 6, 1, 7, 4, 5 }},
        {{ 4, 9, 6, 3, 2, 7, 8, 5, 1 }},
        {{ 8, 1, 3, 4, 5, 6, 9, 7, 2 }},
        {{ 2, 5, 7, 1, 9, 8, 4, 3, 6 }},
        {{ 9, 6, 4, 7, 1, 5, 3, 2, 8 }},
        {{ 7, 3, 1, 6, 8, 2, 5, 9, 4 }},
        {{ 5, 2, 8, 9, 3, 4, 1, 6, 7 }}
    }});

    sudoku::Grid sample_grid_2({{
        {{ 1, 7, 2, 5, 4, 9, 6, 8, 3 }},
        {{ 6, 4, 5, 8, 7, 3, 2, 1, 9 }},
        {{ 3, 8, 9, 2, 6, 1, 7, 4, 5 }},
        {{ 4, 9, 6, 3, 2, 7, 8, 5, 1 }},
        {{ 8, 1, 3, 4, 5, 6, 9, 7, 2 }},
        {{ 2, 5, 7, 1, 9, 8, 4, 3, 6 }},
        {{ 9, 6, 4, 7, 1, 5, 3, 2, 8 }},
        {{ 7, 3, 1, 6, 8, 2, 5, 9, 4 }},
        {{ 5, 2, 8, 9, 3, 4, 1, 6, 7 }}
    }});

    if (sample_grid_1 == sample_grid_2) std::cout << "They're the same! \n\n";

    // Get grid value for coordinate.
    std::pair<int, int> last_coord = std::make_pair(8, 8);
    int last_value = sample_grid_1.get(last_coord);

    // Print the grid to the console.
    std::cout << sample_grid_2 << std::endl;

    return 0;
}
