#include "sudoku.hh"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Constructor: initialize SIZE x SIZE grid filled with spaces
Sudoku::Sudoku() : grid_(SIZE, vector<char>(SIZE, ' '))
{
}

// Check if the given row and column indices are within the grid
bool Sudoku::is_valid_index(int i, int j) const
{
    return i >= 0 and i < static_cast<int>(SIZE)
           and j >= 0 and j < static_cast<int>(SIZE);
}

// Check if the given character is allowed in the Sudoku grid
// Allowed characters are space (empty) and digits '1'–'9'
bool Sudoku::is_valid_char(char c) const
{
    return c == ' ' or (c >= '1' and c <= '9');
}

// Set character c to cell (i, j) if the indices and character are valid
void Sudoku::set(int i, int j, char c)
{
    // Check if cell indices are valid
    if(not is_valid_index(i, j))
    {
        cout << "Trying to access illegal cell (" << i
             << ", " << j << ")!" << endl;
        return;
    }

    // Check if character is allowed
    if(not is_valid_char(c))
    {
        cout << "Trying to set illegal character " << c
             << " to (" << i << ", " << j << ")!" << endl;
        return;
    }

    // Set the value to the grid
    grid_.at(i).at(j) = c;
}

// Check whether the Sudoku grid is legal
bool Sudoku::check() const
{
    // ----- Check rows -----
    // Each row must contain digits 1-9 at most once
    for(unsigned int row = 0; row < SIZE; ++row)
    {
        vector<int> counts(SIZE + 1, 0);

        for(unsigned int col = 0; col < SIZE; ++col)
        {
            char current = grid_.at(row).at(col);
            if(current != ' ')
            {
                ++counts.at(current - '0');
            }
        }

        // Find smallest repeating digit
        for(unsigned int digit = 1; digit <= SIZE; ++digit)
        {
            if(counts.at(digit) > 1)
            {
                cout << "Row " << row << " has multiple "
                     << digit << "'s!" << endl;
                return false;
            }
        }
    }

    // ----- Check columns -----
    // Each column must contain digits 1-9 at most once
    for(unsigned int col = 0; col < SIZE; ++col)
    {
        vector<int> counts(SIZE + 1, 0);

        for(unsigned int row = 0; row < SIZE; ++row)
        {
            char current = grid_.at(row).at(col);
            if(current != ' ')
            {
                ++counts.at(current - '0');
            }
        }

        for(unsigned int digit = 1; digit <= SIZE; ++digit)
        {
            if(counts.at(digit) > 1)
            {
                cout << "Column " << col << " has multiple "
                     << digit << "'s!" << endl;
                return false;
            }
        }
    }

    // ----- Check 3x3 blocks -----
    // Each sub-block must contain digits 1-9 at most once
    for(unsigned int start_row = 0; start_row < SIZE; start_row += BLOCK_SIZE)
    {
        for(unsigned int start_col = 0; start_col < SIZE; start_col += BLOCK_SIZE)
        {
            vector<int> counts(SIZE + 1, 0);

            for(unsigned int row = start_row; row < start_row + BLOCK_SIZE; ++row)
            {
                for(unsigned int col = start_col; col < start_col + BLOCK_SIZE; ++col)
                {
                    char current = grid_.at(row).at(col);
                    if(current != ' ')
                    {
                        ++counts.at(current - '0');
                    }
                }
            }

            for(unsigned int digit = 1; digit <= SIZE; ++digit)
            {
                if(counts.at(digit) > 1)
                {
                    cout << "Block at (" << start_row << ", "
                         << start_col << ") has multiple "
                         << digit << "'s!" << endl;
                    return false;
                }
            }
        }
    }

    // If no duplicates found, Sudoku grid is legal
    return true;
}

// Print the Sudoku grid with borders
void Sudoku::print() const
{
    const string thick_border = "#####################################";
    const string thin_border = "#---+---+---#---+---+---#---+---+---#";

    for(unsigned int row = 0; row < SIZE; ++row)
    {
        // Print thick border every BLOCK_SIZE rows
        if(row % BLOCK_SIZE == 0)
        {
            cout << thick_border << endl;
        }
        else
        {
            cout << thin_border << endl;
        }

        // Print row contents
        for(unsigned int col = 0; col < SIZE; ++col)
        {
            if(col % BLOCK_SIZE == 0)
            {
                cout << "#";
            }
            else
            {
                cout << "|";
            }

            cout << " " << grid_.at(row).at(col) << " ";
        }

        cout << "#" << endl;
    }

    // Print final border
    cout << thick_border << endl;
}