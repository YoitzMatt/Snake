# Snake

A classic Snake game that runs in the terminal, written in C++.

## Build & Run

```bash
clang++ -std=c++17 src/main.cc src/game.cc -o snake
./snake
```

## How to Play

At the menu, press:

- **Y** — Start game
- **H** — Show rules
- **Q** — Quit

During gameplay:

- **W** — Move up
- **A** — Move left
- **S** — Move down
- **D** — Move right
- **Q** — Quit to menu

The snake moves automatically in the last direction pressed. Eat food (`*`) to grow and score points. The game ends if you hit a wall or yourself.

## Gameplay

```
Score: 3   WASD = steer   Q = quit
+----------------------------------------+
|                                        |
|                                        |
|          *                             |
|                                        |
|        @###                            |
|                                        |
+----------------------------------------+
```

- `@` — snake head
- `#` — snake body
- `*` — food

## Requirements

- C++17
- clang++ (or g++ with `-std=c++17`)
- POSIX terminal (macOS / Linux)

## Issues
- You instantly die when going in the opposite direction you're moving in
- Seem to move faster going up and down as opposed to left and right
