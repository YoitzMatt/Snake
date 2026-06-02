#include "game.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <chrono>
#include <thread>

// ── Grid ─────────────────────────────────────────────────────────────────────

void Snake::Grid::Init(int r, int c)
{
    rows = r;
    cols = c;
    cells.assign(rows, std::vector<int>(cols, 0));
}

int Snake::Grid::Rows() const { return rows; }
int Snake::Grid::Cols() const { return cols; }

void Snake::Grid::SetCell(int r, int c, int val)
{
    if (r >= 0 && r < rows && c >= 0 && c < cols)
        cells[r][c] = val;
}

int Snake::Grid::GetCell(int r, int c) const
{
    if (r >= 0 && r < rows && c >= 0 && c < cols)
        return cells[r][c];
    return -1;
}

// Cell values: 0=empty  1=body  2=food  3=head
void Snake::Grid::Display() const
{
    std::cout << '+';
    for (int c = 0; c < cols; c++) std::cout << '-';
    std::cout << "+\n";

    for (int r = 0; r < rows; r++) {
        std::cout << '|';
        for (int c = 0; c < cols; c++) {
            switch (cells[r][c]) {
                case 1:  std::cout << '#'; break;
                case 2:  std::cout << '*'; break;
                case 3:  std::cout << '@'; break;
                default: std::cout << ' '; break;
            }
        }
        std::cout << "|\n";
    }

    std::cout << '+';
    for (int c = 0; c < cols; c++) std::cout << '-';
    std::cout << "+\n";
}

// ── Vec ───────────────────────────────────────────────────────────────────────

Snake::Vec Snake::Vec::operator+(const Vec& other) const
{
    return Vec(row + other.row, col + other.col);
}

bool Snake::Vec::operator==(const Vec& other) const
{
    return row == other.row && col == other.col;
}

// ── Terminal utilities ────────────────────────────────────────────────────────

static struct termios orig_termios;

void Snake::enableRawMode()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~static_cast<unsigned int>(ECHO | ICANON);
    raw.c_cc[VMIN]  = 0;  // non-blocking: return immediately
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void Snake::disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void Snake::clearScreen()
{
    std::cout << "\033[2J\033[H";
}

// ── Player ────────────────────────────────────────────────────────────────────

int Snake::Player::GetInput() const
{
    unsigned char ch;
    return (read(STDIN_FILENO, &ch, 1) == 1) ? ch : 0;
}

void Snake::Player::PlaceFood()
{
    std::vector<Vec> empty;
    for (int r = 0; r < grid.Rows(); r++)
        for (int c = 0; c < grid.Cols(); c++)
            if (grid.GetCell(r, c) == 0)
                empty.push_back(Vec(r, c));

    if (empty.empty()) return;
    food = empty[rand() % static_cast<int>(empty.size())];
    grid.SetCell(food.row, food.col, 2);
}

void Snake::Player::InitGame()
{
    srand(static_cast<unsigned>(time(nullptr)));
    grid.Init(ROWS, COLS);
    body.clear();
    score = 0;

    // Three-segment snake in the center, moving right
    int sr = ROWS / 2;
    int sc = COLS / 2;
    body.push_back(Vec(sr, sc));
    body.push_back(Vec(sr, sc - 1));
    body.push_back(Vec(sr, sc - 2));

    direction = Vec(0, 1);

    grid.SetCell(body[0].row, body[0].col, 3);
    for (size_t i = 1; i < body.size(); i++)
        grid.SetCell(body[i].row, body[i].col, 1);

    PlaceFood();
}

// Returns false when the move results in a collision (game over).
bool Snake::Player::Move()
{
    Vec newHead = body.front() + direction;

    // Wall collision
    if (newHead.row < 0 || newHead.row >= grid.Rows() ||
        newHead.col < 0 || newHead.col >= grid.Cols())
        return false;

    bool ate = (newHead == food);

    // Self collision — if not eating, the tail will vacate, so exclude it
    int checkLen = ate ? static_cast<int>(body.size())
                       : static_cast<int>(body.size()) - 1;
    for (int i = 0; i < checkLen; i++)
        if (newHead == body[i]) return false;

    // Remove tail (unless we just ate)
    if (!ate) {
        grid.SetCell(body.back().row, body.back().col, 0);
        body.pop_back();
    } else {
        score++;
        PlaceFood();
    }

    // Advance head
    grid.SetCell(body.front().row, body.front().col, 1); // old head → body
    body.push_front(newHead);
    grid.SetCell(newHead.row, newHead.col, 3);            // new head

    return true;
}

void Snake::Player::StartGame()
{
    InitGame();
    enableRawMode();

    const int tickMs = 150;
    bool running = true;

    while (running) {
        clearScreen();
        std::cout << "Score: " << score << "   WASD = steer   Q = quit\n";
        grid.Display();
        std::cout.flush();

        int key = GetInput();
        if (key >= 'A' && key <= 'Z') key += 32; // normalize to lowercase

        switch (key) {
            case 'w': 
              if (direction.row !=  1) { 
                direction = Vec(-1,  0);
              }

              break;
            case 's': 

              if (direction.row != -1) { 
                direction = Vec( 1,  0); 
              } 

              break;
            case 'a': 
              if (direction.col !=  1)  { 
                direction = Vec( 0, -1); 
              } 

              break;
            case 'd': 
              if (direction.col != -1) { 
                direction = Vec( 0,  1); 
              } 

              break;
            case 'q': running = false; break;
        }

        if (running && !Move()) {
            clearScreen();
            std::cout << "Game Over!  Final score: " << score << "\n\n";
            running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(tickMs));
    }

    disableRawMode();
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// ── Misc ──────────────────────────────────────────────────────────────────────

void Snake::showRules()
{
    std::cout << "\n========== RULES ==========\n";
    std::cout << "Use WASD to steer the snake.\n";
    std::cout << "Eat food (*) to grow and score points.\n";
    std::cout << "Avoid hitting walls or yourself!\n";
    std::cout << "Press Q during gameplay to quit.\n";
    std::cout << "============================\n\n";
}

void Snake::showHelp()
{
    std::cout << "\n========== SNAKE ==========\n";
    std::cout << "  Y - Start game\n";
    std::cout << "  H - Show rules\n";
    std::cout << "  Q - Quit\n";
    std::cout << "===========================\n";
    std::cout << "Enter your choice: ";
}
