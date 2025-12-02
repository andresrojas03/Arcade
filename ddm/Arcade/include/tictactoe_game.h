#pragma once
#include "shared_graphics.h"
#include "shared_input.h"

class TicTacToeGame {
private:
    // Game state 
    char board[3][3];
    char currentPlayer;
    bool gameOver;
    char winner;
    
    // Cursor position for navigation
    int cursorRow;
    int cursorCol;
    
    // Helper methods 
    void displayBoard();
    void getPlayerInput();
    bool isValidMove(int row, int col);
    bool checkWin(char player);
    bool checkDraw();
    void switchPlayer();
    void displayWinner();
    void displayDraw();
    void resetGame();
    
    // Drawing helpers
    void drawGrid();
    void drawSymbol(int row, int col, char symbol);
    void drawCursor();

public:
    void initialize();
    int run(); // Returns: 0=playing, 1=game over, 2=quit
    void cleanup();
};