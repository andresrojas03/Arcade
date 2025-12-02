#pragma once
#include "shared_graphics.h"
#include "shared_input.h"

class PongGame{
private:
    // Game constants
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    static const int PADDLE_WIDTH = 4;
    static const int PADDLE_HEIGHT = 16;
    static const int BALL_SIZE = 4;
    static const int MAX_SCORE = 5;
    
    // Game state 
    int playerY;
    int comY;
    int ballX, ballY;
    int ballDX, ballDY;
    int playerScore;
    int comScore;
    bool gameRunning;
    
    // Helper methods
    void resetBall();
    void updateAI();
    bool checkPaddleCollision(int paddleX, int paddleY);
    void drawPaddle(int x, int y);
    void drawBall();
    void drawScores();
    void drawNet();

public:
    void initialize();
    int run();  // Returns game state: 0=playing, 1=game over, 2=quit
    void cleanup();
};