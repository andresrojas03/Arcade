#include "Pong_game.h"
#include "shared_input.h"
void PongGame::initialize() {
    // Initialize positions
    playerY = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    comY = (SCREEN_HEIGHT - PADDLE_HEIGHT) / 2;
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballDX = 2;  // Horizontal speed
    ballDY = 1;  // Vertical speed
    playerScore = 0;
    comScore = 0;
    gameRunning = true;
}

int PongGame::run() {
    if (!gameRunning) return 1;
    
    // Input handling 
    SharedInput::Button btn = SharedInput::getButton();
    if (btn == SharedInput::UP && playerY > 0) {
        playerY -= 3;
    }
    else if (btn == SharedInput::DOWN && playerY < SCREEN_HEIGHT - PADDLE_HEIGHT) {
        playerY += 3;
    }
    else if (btn == SharedInput::DENY) {
        return 2; // Quit to menu
    }
    
    // Ball movement 
    int newBallX = ballX + ballDX;
    int newBallY = ballY + ballDY;
    
    // Top/Bottom wall collision
    if (newBallY <= 0 || newBallY >= SCREEN_HEIGHT - BALL_SIZE) {
        ballDY = -ballDY;
        newBallY = ballY + ballDY;
    }
    
    // Paddle collisions
    bool playerCollision = checkPaddleCollision(SCREEN_WIDTH - PADDLE_WIDTH - 2, playerY);
    bool comCollision = checkPaddleCollision(2, comY);
    
    if (playerCollision || comCollision) {
        ballDX = -ballDX;
        // Add some randomness to ball angle after paddle hit
        ballDY += (random(-1, 2));
        ballDY = constrain(ballDY, -2, 2); // Limit vertical speed
    }
    
    // Score update
    if (newBallX <= 0) {
        playerScore++;
        resetBall();
    }
    else if (newBallX >= SCREEN_WIDTH - BALL_SIZE) {
        comScore++;
        resetBall();
    }
    else {
        // Update ball position if no scoring
        ballX = newBallX;
        ballY = newBallY;
    }
    
    // Update AI (simple follow-the-ball)
    updateAI();
    
    // Drawing (following your algorithm)
    SharedGraphics::clearDisplay();
    drawNet();
    drawPaddle(SCREEN_WIDTH - PADDLE_WIDTH - 2, playerY);  // Player paddle (right)
    drawPaddle(2, comY);                                   // COM paddle (left)
    drawBall();
    drawScores();
    SharedGraphics::updateDisplay();
    
    // Game over check (following your algorithm)
    if (playerScore >= MAX_SCORE || comScore >= MAX_SCORE) {
        gameRunning = false;
        return 1; // Game over
    }
    
    delay(50); // Game speed
    return 0; // Still playing
}

void PongGame::resetBall() {
    ballX = SCREEN_WIDTH / 2;
    ballY = SCREEN_HEIGHT / 2;
    ballDX = (ballDX > 0) ? -2 : 2; // Alternate direction
    ballDY = random(-1, 2);
}

void PongGame::updateAI() {
    // Simple AI: follow the ball with some delay
    int targetY = ballY - PADDLE_HEIGHT / 2;
    
    if (comY < targetY && comY < SCREEN_HEIGHT - PADDLE_HEIGHT) {
        comY += 1;
    }
    else if (comY > targetY && comY > 0) {
        comY -= 1;
    }
}

bool PongGame::checkPaddleCollision(int paddleX, int paddleY) {
    return (ballX + BALL_SIZE >= paddleX && ballX <= paddleX + PADDLE_WIDTH &&
            ballY + BALL_SIZE >= paddleY && ballY <= paddleY + PADDLE_HEIGHT);
}

void PongGame::drawPaddle(int x, int y) {
    SharedGraphics::drawRect(x, y, PADDLE_WIDTH, PADDLE_HEIGHT, true);
}

void PongGame::drawBall() {
    SharedGraphics::drawRect(ballX, ballY, BALL_SIZE, BALL_SIZE, true);
}

void PongGame::drawScores() {
    // Player score (right)
    SharedGraphics::drawText(SCREEN_WIDTH - 20, 5, String(playerScore).c_str(), 2);
    // COM score (left)
    SharedGraphics::drawText(10, 5, String(comScore).c_str(), 2);
}

void PongGame::drawNet() {
    // Draw dashed center line
    for (int y = 0; y < SCREEN_HEIGHT; y += 8) {
        SharedGraphics::drawLine(SCREEN_WIDTH / 2, y, SCREEN_WIDTH / 2, y + 4);
    }
}

void PongGame::cleanup() {
    gameRunning = false;
}