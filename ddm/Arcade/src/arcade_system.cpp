#include "arcade_system.h"
#include "Pong_game.h"
#include "Snake_game.h"
#include "tictactoe_game.h"

const char PROGMEM GAME_NAMES[][12] = {"SNAKE", "PONG", "TIC TAC TOE"};
const int TOTAL_GAMES = 3;

void ArcadeSystem::initialize() {
    SharedGraphics::initialize();
    SharedInput::initialize();
    currentState = STATE_BOOT;
    currentGameIndex = 0;
    gameRunning = false;
}

void ArcadeSystem::run() {
    switch(currentState) {
        case STATE_BOOT: handleBootState(); break;
        case STATE_MENU: handleMenuState(); break;
        case STATE_GAME_SELECTED: handleGameSelectedState(); break;
        case STATE_GAME_RUNNING: handleGameRunningState(); break;
        case STATE_GAME_PAUSED: handleGamePausedState(); break;
        case STATE_GAME_OVER: handleGameOverState(); break;
    }
}

void ArcadeSystem::handleBootState() {
    SharedGraphics::clearDisplay();
    SharedGraphics::drawText(25, 15, "ARCADE", 2);
    SharedGraphics::drawText(30,35, "Equipo 3", 1);
    SharedGraphics::drawText(2,45, "S. Daniela, U. Andres",1);
    SharedGraphics::updateDisplay();
    delay(2000);
    currentState = STATE_MENU;
}

void ArcadeSystem::handleMenuState() {
    displayRockolaMenu();  
    
    SharedInput::Button btn = SharedInput::getButton();
    if(btn == SharedInput::LEFT) {
        currentGameIndex = (currentGameIndex - 1 + TOTAL_GAMES) % TOTAL_GAMES;
    }
    else if(btn == SharedInput::RIGHT) {
        currentGameIndex = (currentGameIndex + 1) % TOTAL_GAMES;
    }
    else if(btn == SharedInput::SELECT) {
        selectedGame = (GameType)currentGameIndex;
        currentState = STATE_GAME_SELECTED;
    }
}

void ArcadeSystem::handleGameSelectedState() {
    displayGamePreview(selectedGame);
    
    SharedInput::Button btn = SharedInput::getButton();
    if(btn == SharedInput::SELECT) {
        currentState = STATE_GAME_RUNNING;
        // startGame(selectedGame); // Will implement when games are ready
    }
    else if(btn == SharedInput::DENY) {
        currentState = STATE_MENU;
    }
}

void ArcadeSystem::displayRockolaMenu() {
    SharedGraphics::clearDisplay();
    
    // Large centered game name (rockola style)
    char gameName[12];
    strcpy_P(gameName, GAME_NAMES[currentGameIndex]);
    
    // Big centered title
    SharedGraphics::drawText(20, 20, gameName, 3);  // Size 3 for large text
    
    // Decorative elements
    SharedGraphics::drawLine(0, 50, 128, 50);       // Separator line
    
    // Game description below
    /*
    switch((GameType)currentGameIndex) {
        case GAME_SNAKE:
            SharedGraphics::drawText(15, 50, "EAT AND GROW", 1);
            break;
        case GAME_PONG:
            SharedGraphics::drawText(25, 50, "BOUNCE BALL", 1);
            break;
        case GAME_TICTACTOE:
            SharedGraphics::drawText(20, 50, "3 IN A ROW", 1);
            break;
    }
    */
    // Navigation indicators (left/right arrows)
    SharedGraphics::drawText(5, 25, "<", 2);         // Left arrow
    SharedGraphics::drawText(115, 25, ">", 2);       // Right arrow
    
    // Footer instruction
    SharedGraphics::drawText(30, 5, "SELECT GAME", 1);  // Header
    SharedGraphics::drawText(25, 55, "PRESS SELECT", 1); // Footer
    
    SharedGraphics::updateDisplay();
}

void ArcadeSystem::displayGamePreview(GameType game) {
    SharedGraphics::clearDisplay();
    
    char gameName[12];
    strcpy_P(gameName, GAME_NAMES[game]);
    SharedGraphics::drawText(40, 10, gameName);
    SharedGraphics::drawLine(0, 15, 128, 15);
    
    switch(game) {
        case GAME_SNAKE:
            SharedGraphics::drawText(15, 30, "Eat food, grow long");
            break;
        case GAME_PONG:
            SharedGraphics::drawText(25, 30, "Bounce the ball");
            break;
        case GAME_TICTACTOE:
            SharedGraphics::drawText(20, 30, "3 in a row wins");
            break;
    }
    
    SharedGraphics::drawText(10, 55, "CONFIRM: Start  DENY: Back");
    SharedGraphics::updateDisplay();
}

// Placeholder implementations for now
void ArcadeSystem::handleGameRunningState() {
    int gameResult = 0;
    // Declare games outside switch
    static PongGame pongGame;
    static SnakeGame snakeGame;
    static TicTacToeGame tttGame ;
    // static TicTacToeGame tttGame;   
    
     switch(selectedGame) {
        case GAME_PONG:
            if(!gameRunning) {
                pongGame.initialize();
                gameRunning = true;
            }
            gameResult = pongGame.run();
            break;
          
        case GAME_SNAKE:
            if(!gameRunning) {
                snakeGame.initialize();
                gameRunning = true;
            }
            gameResult = snakeGame.run();
            break;
       case GAME_TICTACTOE:
            if(!gameRunning) {
                tttGame.initialize();
                gameRunning = true;
            }
            gameResult = tttGame.run();
            break;
    }
    
    if(gameResult == 1) { // Game over
        currentState = STATE_GAME_OVER;
        gameRunning = false;
    }
    else if(gameResult == 2) { // Quit to menu
        currentState = STATE_MENU;
        gameRunning = false;
    }
}

void ArcadeSystem::handleGamePausedState() {
    // Will implement when games are ready
    currentState = STATE_MENU;
}

void ArcadeSystem::handleGameOverState() {
    // Will implement when games are ready  
    currentState = STATE_MENU;
}