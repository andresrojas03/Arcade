#include "game_manager.h"
#include "shared_graphics.h"

GameManager::GameType GameManager::currentGame = MENU;
GameManager::GameType GameManager::selectedGame = SNAKE;

void GameManager::initialize() {
    SharedGraphics::initialize();
    SharedInput::initialize();
    currentGame = MENU;
}

void GameManager::run() {
    switch(currentGame) {
        case MENU:
            showMenu();
            handleMenuInput();
            break;
        case SNAKE:
            // Snake game will go here
            break;
        case TIC_TAC_TOE:
            // Tic Tac Toe will go here
            break;
        case PONG:
            // Pong will go here
            break;
        default:
            break;
    }
}

void GameManager::showMenu() {
    SharedGraphics::clearDisplay();
    SharedGraphics::drawText(40, 10, "ARCADE MACHINE", 1);
    SharedGraphics::drawText(50, 25, "> Snake", 1);
    SharedGraphics::drawText(50, 35, "  Tic Tac Toe", 1);
    SharedGraphics::drawText(50, 45, "  Pong", 1);
    SharedGraphics::updateDisplay();
}

void GameManager::handleMenuInput() {
    SharedInput::Button btn = SharedInput::getButton();
    // Menu navigation logic here
}

void GameManager::switchGame(GameType newGame) {
    currentGame = newGame;
}