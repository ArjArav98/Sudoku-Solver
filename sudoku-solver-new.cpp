#include<iostream>
#include<fstream>
#include<array>
#include<set>
#include<algorithm>
#include<utility>

class SudokuGrid {
    private:
    std::array< std::array<int,9> ,9> grid;
    std::set< std::pair<int,int> > coords_that_were_pre_filled;

    public:
    SudokuGrid () {
        std::array<int,9> filled_array = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        grid.fill(filled_array);
    }

    friend std::ostream& operator<< (std::ostream& out, SudokuGrid grid);
};

std::ostream& operator<< (std::ostream& out, SudokuGrid grid) {
    out<<"+-------+-------+-------+\n";
    for (int row_index=0; row_index<9; row_index++) {
        out<<"|";
        for (int col_index=0; col_index<9; col_index++) {
            out<<" "<<grid.grid[row_index][col_index];
            if (col_index%3==2) out<<" |";
        }
        out<<"\n";
        if (row_index%3==2) out<<"+-------+-------+-------+\n";
    };
    return out;
}

int main() {
    SudokuGrid grid;
    std::cout<<grid;
    return 0;
}
