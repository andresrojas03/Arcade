#pragma once
#include "shared_graphics.h"
#include "shared_input.h"

enum SystemState {
    STATE_BOOT,
    STATE_MENU,
    STATE_GAME_SELECTED, 
    STATE_GAME_RUNNING,
    STATE_GAME_PAUSED,
    STATE_GAME_OVER
};

enum GameType {
    GAME_SNAKE = 0,
    GAME_PONG,
    GAME_TICTACTOE
};

class ArcadeSystem {
private:
    SystemState currentState;
    GameType selectedGame;
    int currentGameIndex;
    bool gameRunning;

    void handleBootState();
    void handleMenuState();
    void handleGameSelectedState();
    void handleGameRunningState();
    void handleGamePausedState();
    void handleGameOverState();

    void displayRockolaMenu();
    void displayGamePreview(GameType game);
    void startGame(GameType game);
    void stopGame();

public:
    void initialize();
    void run();
};