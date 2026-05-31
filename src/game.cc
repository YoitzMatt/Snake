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

// Vec methods
Snake::Vec Snake::Vec::operator+(const Vec& other) const
{
    return Vec(x + other.x, y + other.y);
}

Snake::Vec Snake::Vec::operator*(float speed) const
{
    return Vec(x * speed, y * speed);
}

void Snake::Vec::Set(float x, float y)
{
  this->x = x;
  this->y = y;
}

// Player methods
void Snake::Player::StartGame()
{
    char input{};
    bool done{false};
    while (!done) {
        Snake::Vec movement{}; 
        std::cin >> input;
        std::tolower(static_cast<unsigned char>(input));

        switch (input) {
            case 'w':
                // move up
                movement.Set(0.0, 1.0);
                Move(movement);
                break;
            case 'a':
                movement.Set(-1.0, 0.0);
                Move(movement);
                break;
            case 's':
                movement.Set(0.0, -1.0);
                Move(movement);
                break;
            case 'd':
                movement.Set(1.0, 0.0);
                Move(movement);
                break;
            default:
                // TODO: implement player moving in last direction they pressed
                break;
        }

        // evaluate outcome after updating player position

    }
}

void Snake::Player::Move(Snake::Vec& movement)
{
    // update the position
    position = position + movement * speed;

    // check if the player has hit the border an apple of another empty cell
}


void Snake::showRules() 
{
    std::cout << "\n========== RULES ==========\n";
    std::cout << "1. The goal of the game is to...\n";
    std::cout << "2. Players take turns...\n";
    std::cout << "3. The first player to... wins!\n";
    std::cout << "============================\n\n";
}
 
void Snake::showHelp() 
{
    std::cout << "\n========== HELP MENU ==========\n";
    std::cout << "  Y - Continue to game\n";
    std::cout << "  H - Show rules\n";
    std::cout << "  Q - Quit\n";
    std::cout << "================================\n";
    std::cout << "Enter your choice: ";
}

