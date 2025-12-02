#include "snake_game.h"

void SnakeGame::initialize() {
    // Initialize snake starting position
    snakeX[0] = 64; // head
    snakeY[0] = 32;
    snakeX[1] = 60; // body
    snakeY[1] = 32;
    snakeX[2] = 56; // tail
    snakeY[2] = 32;
    
    snakeLength = 3;
    direction = 0; // right
    score = 0;
    gameRunning = true;
    gameSpeed = 200;
    lastUpdate = 0;
    
    generateFruit();
}

int SnakeGame::run() {
    if (!gameRunning) return 1;
    
    // Input handling
    SharedInput::Button btn = SharedInput::getButton();
    if (btn == SharedInput::UP && direction != 3) {
        direction = 2;
    }
    else if (btn == SharedInput::DOWN && direction != 2) {
        direction = 3;
    }
    else if (btn == SharedInput::LEFT && direction != 0) {
        direction = 1;
    }
    else if (btn == SharedInput::RIGHT && direction != 1) {
        direction = 0;
    }
    else if (btn == SharedInput::DENY) {
        return 2; // Quit to menu
    }
    
    // Game timing
    unsigned long currentTime = millis();
    if (currentTime - lastUpdate < gameSpeed) {
        return 0; // Still playing, wait for next frame
    }
    lastUpdate = currentTime;
    
    // Calculate new head position
    int newHeadX = snakeX[0];
    int newHeadY = snakeY[0];
    
    switch(direction) {
        case 0: newHeadX += GRID_SIZE; break; // right
        case 1: newHeadX -= GRID_SIZE; break; // left
        case 2: newHeadY -= GRID_SIZE; break; // up
        case 3: newHeadY += GRID_SIZE; break; // down
    }
    
    // Screen wrapping
    if (newHeadX >= SCREEN_WIDTH) newHeadX = 0;
    if (newHeadX < 0) newHeadX = SCREEN_WIDTH - GRID_SIZE;
    if (newHeadY >= SCREEN_HEIGHT) newHeadY = 0;
    if (newHeadY < 0) newHeadY = SCREEN_HEIGHT - GRID_SIZE;
    
    // Check self collision
    for (int i = 0; i < snakeLength; i++) {
        if (snakeX[i] == newHeadX && snakeY[i] == newHeadY) {
            return 1; // Game over
        }
    }
    
    // Move snake body
    for (int i = snakeLength; i > 0; i--) {
        snakeX[i] = snakeX[i-1];
        snakeY[i] = snakeY[i-1];
    }
    
    // Update head position
    snakeX[0] = newHeadX;
    snakeY[0] = newHeadY;
    
    // Check fruit collision
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        snakeLength++;
        score++;
        generateFruit();
        
        // Increase speed
        if (gameSpeed > 50) {
            gameSpeed -= 5;
        }
        
        // Prevent overflow
        if (snakeLength >= MAX_SNAKE_LENGTH) {
            snakeLength = MAX_SNAKE_LENGTH;
        }
    }
    
    // Drawing
    SharedGraphics::clearDisplay();
    drawSnake();
    drawFruit();
    
    // Draw score
    SharedGraphics::drawText(0, 0, "SCORE:");
    SharedGraphics::drawText(40, 0, String(score).c_str());
    
    SharedGraphics::updateDisplay();
    
    return 0; // Still playing
}

void SnakeGame::generateFruit() {
    bool validPosition = false;
    int attempts = 0;
    
    while (!validPosition && attempts < 100) {
        fruitX = (random(0, SCREEN_WIDTH / GRID_SIZE)) * GRID_SIZE;
        fruitY = (random(3, SCREEN_HEIGHT / GRID_SIZE)) * GRID_SIZE; // Avoid top area
        
        validPosition = true;
        // Check if fruit doesn't overlap with snake
        for (int i = 0; i < snakeLength; i++) {
            if (snakeX[i] == fruitX && snakeY[i] == fruitY) {
                validPosition = false;
                break;
            }
        }
        attempts++;
    }
}

void SnakeGame::drawSnake() {
    for (int i = 0; i < snakeLength; i++) {
        SharedGraphics::drawRect(snakeX[i], snakeY[i], GRID_SIZE, GRID_SIZE, true);
    }
}

void SnakeGame::drawFruit() {
    SharedGraphics::drawRect(fruitX, fruitY, GRID_SIZE, GRID_SIZE, true);
}

void SnakeGame::resetGame() {
    // Could be used for restart
    initialize();
}

void SnakeGame::cleanup() {
    gameRunning = false;
}