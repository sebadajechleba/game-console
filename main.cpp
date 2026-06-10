#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

const int WIDTH = 30;
const int HEIGHT = 20;

struct Point {
    int x;
    int y;
};

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

void clearScreen() {
    std::system("cls");
}

void draw(const std::vector<Point>& snake, const Point& food, int score) {
    clearScreen();
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == 0 || x == WIDTH - 1 || y == 0 || y == HEIGHT - 1) {
                std::cout << '#';
            } else if (x == food.x && y == food.y) {
                std::cout << 'O';
            } else {
                bool printed = false;
                for (size_t k = 0; k < snake.size(); ++k) {
                    if (snake[k].x == x && snake[k].y == y) {
                        std::cout << (k == 0 ? '@' : 'o');
                        printed = true;
                        break;
                    }
                }
                if (!printed) std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << "Score: " << score << "\n";
    std::cout << "Use WASD to move, Q to quit.\n";
}

bool collision(const std::vector<Point>& snake) {
    const Point& head = snake.front();
    if (head.x <= 0 || head.x >= WIDTH - 1 || head.y <= 0 || head.y >= HEIGHT - 1) return true;
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[i].x == head.x && snake[i].y == head.y) return true;
    }
    return false;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<Point> snake = {{WIDTH / 2, HEIGHT / 2}};
    Point food = {std::rand() % (WIDTH - 2) + 1, std::rand() % (HEIGHT - 2) + 1};
    Direction dir = STOP;
    int score = 0;
    bool running = true;

    draw(snake, food, score);
    while (running) {
        if (_kbhit()) {
            char key = static_cast<char>(std::toupper(_getch()));
            if (key == 'Q') break;
            if (key == 'A' && dir != RIGHT) dir = LEFT;
            if (key == 'D' && dir != LEFT) dir = RIGHT;
            if (key == 'W' && dir != DOWN) dir = UP;
            if (key == 'S' && dir != UP) dir = DOWN;
        }

        if (dir != STOP) {
            Point newHead = snake.front();
            switch (dir) {
                case LEFT: newHead.x -= 1; break;
                case RIGHT: newHead.x += 1; break;
                case UP: newHead.y -= 1; break;
                case DOWN: newHead.y += 1; break;
                default: break;
            }
            snake.insert(snake.begin(), newHead);
            if (newHead.x == food.x && newHead.y == food.y) {
                score += 10;
                do {
                    food.x = std::rand() % (WIDTH - 2) + 1;
                    food.y = std::rand() % (HEIGHT - 2) + 1;
                } while (std::any_of(snake.begin(), snake.end(), [&](const Point& p) { return p.x == food.x && p.y == food.y; }));
            } else {
                snake.pop_back();
            }

            if (collision(snake)) {
                running = false;
            }
        }

        draw(snake, food, score);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "Game Over! Final score: " << score << "\n";
    std::cout << "Press any key to exit...\n";
    _getch();
    return 0;
}