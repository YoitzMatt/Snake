#include <cctype>
#include <iostream>
#include <memory>
#include "game.hpp"

// TODO:
// 1.) make snake appear on the screen 
// 2.) make snake move
// 3.) make snake respond to player input
auto main(void) -> int
{
  char input = {};
  Snake::showHelp();

  while (true) {
    std::cin >> input;
    input = std::tolower(static_cast<unsigned char>(input)); 
      switch (input) {
      case 'h':
        Snake::showRules();
        continue;
      case 'y':
        std::cout << "starting game...." << std::endl;
        break;
      case 'q':
        std::cout << "exiting Game" << std::endl;
        return 0;
      default:
        std::cout << "Invalid option chosen" << std::endl;
        Snake::showHelp();
        continue;
    }

      // Game start
      std::unique_ptr<Snake::Grid> grid{new Snake::Grid};
      grid->Init(COL, ROW);

      std::unique_ptr<Snake::Player> p{new Snake::Player};
      p->StartGame();
  }

  return 0;
}
