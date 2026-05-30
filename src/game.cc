#include "game.hpp"
#include "vector"

// initalizes the row and column size 
// then sets all the values in the grid to 0
void Snake::Grid::Init(int row, int col)
{
    this->row = row; 
    this->col = col;
    cells.assign(row, std::vector<int>(col, 0));
    return;
}

// return the snake grid
std::vector<std::vector<int>> Snake::Grid::Get()
{
    return this->cells;
}

// returns the size of the grid
// TODO: implement
int Snake::Grid::Size()
{
    return -1;
}

// Prints the Grid to the terminal
void Snake::Grid::Display()
{
    //TODO: implement
}