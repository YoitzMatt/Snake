#ifndef GAME_H
#define GAME_H
#include <vector>

namespace Snake 
{
    class Grid {
        public:
            std::vector<std::vector<int>> cells;
            void Init(int col, int row);
            std::vector<std::vector<int>> Get();
            void Display();

        private:
            int col;
            int row;
    };
}

#endif // GAME_H
