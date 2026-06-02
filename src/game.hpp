#ifndef GAME_H
#define GAME_H

#include <vector>
#include <deque>
#include <memory>

const int ROWS = 20;
const int COLS = 40;

namespace Snake
{
    class Grid {
    public:
        void Init(int rows, int cols);
        void Display() const;
        void SetCell(int row, int col, int val);
        int  GetCell(int row, int col) const;
        int  Rows() const;
        int  Cols() const;

    private:
        std::vector<std::vector<int>> cells;
        int rows = 0;
        int cols = 0;
    };

    // Integer 2D vector — row/col on the grid
    struct Vec {
        int row;
        int col;
        Vec(int row = 0, int col = 0) : row(row), col(col) {}
        Vec operator+(const Vec& other) const;
        bool operator==(const Vec& other) const;
    };

    class Player {
    public:
        void StartGame();

    private:
        Grid             grid;
        std::deque<Vec>  body;      // body[0] = head
        Vec              direction;
        Vec              food;
        int              score = 0;

        void InitGame();
        bool Move();                // returns false on collision (game over)
        void PlaceFood();
        int  GetInput() const;      // non-blocking; returns char or 0
    };

    void showRules();
    void showHelp();
    void clearScreen();
    void enableRawMode();
    void disableRawMode();
}

#endif // GAME_H
