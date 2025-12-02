#pragma once
#include "shared_input.h"

class GameManager {
public:
    enum GameType {
        NO_GAME = -1,
        SNAKE = 0,
        TIC_TAC_TOE,
        PONG,
        MENU
    };
    
    static void initialize();
    static void run();
    static void switchGame(GameType newGame);
    
private:
    static GameType currentGame;
    static GameType selectedGame;
    static void showMenu();
    static void handleMenuInput();
};