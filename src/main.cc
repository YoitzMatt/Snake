#include <cctype>
#include <iostream>
#include <memory>
#include "game.hpp"

void showRules() 
{
    std::cout << "\n========== RULES ==========\n";
    std::cout << "1. The goal of the game is to...\n";
    std::cout << "2. Players take turns...\n";
    std::cout << "3. The first player to... wins!\n";
    std::cout << "============================\n\n";
}
 
void showHelp() 
{
    std::cout << "\n========== HELP MENU ==========\n";
    std::cout << "  Y - Continue to game\n";
    std::cout << "  H - Show rules\n";
    std::cout << "  Q - Quit\n";
    std::cout << "================================\n";
    std::cout << "Enter your choice: ";
}

// TODO:
// 1.) handle game starting input 
// 2.) create grid
// 3.) handle game events

auto main(void) -> int
{
  char input = {};
  showHelp();
  while (true) {
    std::cin >> input;
    input = std::tolower(static_cast<unsigned char>(input)); 
      switch (input) {
      case 'h':
        showRules();
        continue;
      case 'y':
        std::cout << "starting game...." << std::endl;
        break;
      case 'q':
        std::cout << "exiting Game" << std::endl;
        return 0;
      default:
        std::cout << "Invalid option chosen" << std::endl;
        showHelp();
        continue;
    }

      // Game start
      std::unique_ptr<Snake::Grid> grid{new Snake::Grid};
      grid->Init(20, 100);
      
  }
  return 0;
}
