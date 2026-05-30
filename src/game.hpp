#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>

namespace Snake 
{
    class Grid {
        public:
            std::vector<std::vector<int>> cells;
            void Init(int col, int row);
            std::vector<std::vector<int>> Get();
            int Size();
            void Display();

        private:
            int col;
            int row;
    };
}

#endif // GAME_H