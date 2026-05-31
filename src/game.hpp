#ifndef GAME_H
#define GAME_H
#include <vector>

const int ROW{100};
const int COL{20};
const int START_POS{(ROW - 1 / 2)};

namespace Snake 
{
    class Grid {
        public:
            void Init(int col, int row);
            void Display();
            std::vector<std::vector<int>> Get();

        private:
            std::vector<std::vector<int>> cells;
            int col;
            int row;
    };

    class Vec {
        public:
            float x;
            float y;
            Vec(float x = 0, float y = 0) : x(x), y(y) {}
            void Set(float x, float y); 
            Vec operator+(const Vec& other) const;
            Vec operator*(float speed) const;
    };

    class Player {
      public:
        void StartGame();
        void Move(Snake::Vec& movement);
        Snake::Vec position;

        private:
            std::vector<int> snake;
            std::unique_ptr<Snake::Grid> grid;
            float speed;
    };

    void showRules();
    void showHelp(); 
}


#endif // GAME_H
