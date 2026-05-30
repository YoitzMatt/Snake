#include "game.hpp"
#include "vector"
#include <iostream>

// initalizes the row and column size 
// then sets all the values in the grid to 0
void Snake::Grid::Init(int row, int col)
{
    this->row = row; 
    this->col = col;
    std::cout << "bug here" << std::endl;
    cells.assign(row, std::vector<int>(col, 0));
    std::cout << "bug here" << std::endl;
    return;
}

// returns the snake grid
std::vector<std::vector<int>> Snake::Grid::Get()
{
    return this->cells;
}

// Prints the Grid to the terminal
void Snake::Grid::Display()
{
    int r = this->row;
    int c = this->col;
    for (int i{}; i < row; i++) {
      for (int j{}; j < col; j++) {
        std::cout << "x";
      }
      std::cout << std::endl;
   }
}
