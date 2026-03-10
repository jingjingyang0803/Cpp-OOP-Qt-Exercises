#ifndef SUDOKU_HH
#define SUDOKU_HH

#include <vector>

// Sizes of a block and the whole sudoku
const unsigned int BLOCK_SIZE = 3;
const unsigned int SIZE = 3 * BLOCK_SIZE;

// Class representing a Sudoku grid and operations on it
class Sudoku
{
public:
    // Constructor: initializes an empty SIZE x SIZE Sudoku grid
    Sudoku();

    // Sets character c to cell (i, j)
    // Prints an error message if indices or character are invalid
    void set(int i, int j, char c);

    // Checks whether the Sudoku grid is legal
    // Returns true if legal, false otherwise
    bool check() const;

    // Prints the Sudoku grid with borders
    void print() const;

private:
    // 2D grid storing Sudoku values
    std::vector<std::vector<char>> grid_;

    // Checks if indices are within valid range
    bool is_valid_index(int i, int j) const;

    // Checks if character is allowed in Sudoku
    bool is_valid_char(char c) const;
};

#endif // SUDOKU_HH
