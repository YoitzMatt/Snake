#include <iostream>
#include "game.hpp"

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
            break;
        case 'q':
            std::cout << "Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid option.\n";
            Snake::showHelp();
            continue;
        }

        Snake::Player p;
        p.StartGame();
        Snake::showHelp();
    }

    return 0;
}
