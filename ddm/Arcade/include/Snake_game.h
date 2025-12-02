#pragma once
#include "shared_graphics.h"
#include "shared_input.h"

class SnakeGame {
private:
    // Optimized memory usage
    static const int MAX_SNAKE_LENGTH = 30;
    static const int GRID_SIZE = 4;
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    
    // Game state (separate arrays to save memory)
    int snakeX[MAX_SNAKE_LENGTH];
    int snakeY[MAX_SNAKE_LENGTH];
    int snakeLength;
    int fruitX, fruitY;
    int direction; // 0=right, 1=left, 2=up, 3=down
    int score;
    bool gameRunning;
    unsigned long lastUpdate;
    int gameSpeed;
    
    // Helper methods
    void generateFruit();
    void updateSnakePosition();
    bool checkSelfCollision();
    void drawSnake();
    void drawFruit();
    void resetGame();

public:
    void initialize();
    int run(); // Returns: 0=playing, 1=game over, 2=quit
    void cleanup();
};