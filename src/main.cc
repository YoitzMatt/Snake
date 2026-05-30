#include <cctype>
#include <iostream>
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

    // Game logic
    Snake::Grid ng;
    ng.Init(10, 10);
  }
  
  return 0;
}
