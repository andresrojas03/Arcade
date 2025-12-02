#include "tictactoe_game.h"

void TicTacToeGame::initialize() {
    // Initialize board 
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
    
    currentPlayer = 'X';
    gameOver = false;
    winner = ' ';
    cursorRow = 1;
    cursorCol = 1;
}

int TicTacToeGame::run() {
    if(gameOver) {
        // Show end screen for 2 seconds, then return to menu
        delay(2000);
        return 1;
    }
    
    displayBoard();
    
    // Input handling using your 6 buttons
    SharedInput::Button btn = SharedInput::getButton();
    
    if(btn == SharedInput::UP && cursorRow > 0) {
        cursorRow--;
    }
    else if(btn == SharedInput::DOWN && cursorRow < 2) {
        cursorRow++;
    }
    else if(btn == SharedInput::LEFT && cursorCol > 0) {
        cursorCol--;
    }
    else if(btn == SharedInput::RIGHT && cursorCol < 2) {
        cursorCol++;
    }
    else if(btn == SharedInput::SELECT) {
        // Make move 
        if(isValidMove(cursorRow, cursorCol)) {
            board[cursorRow][cursorCol] = currentPlayer;
            
            // Check win 
            if(checkWin(currentPlayer)) {
                gameOver = true;
                winner = currentPlayer;
                displayBoard();
                displayWinner();
                return 0; // Still in game to show winner
            }
            
            // Check draw 
            if(checkDraw()) {
                gameOver = true;
                displayBoard();
                displayDraw();
                return 0; // Still in game to show draw
            }
            
            // Switch player 
            switchPlayer();
        }
    }
    else if(btn == SharedInput::DENY) {
        return 2; // Quit to menu
    }
    
    delay(150); // Responsive controls
    return 0; // Still playing
}

void TicTacToeGame::displayBoard() {
    SharedGraphics::clearDisplay();
    drawGrid();
    
    // Draw all symbols
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] != ' ') {
                drawSymbol(i, j, board[i][j]);
            }
        }
    }
    
    // Draw cursor if game not over
    if(!gameOver) {
        drawCursor();
    }
    
    // Draw player turn or result
    SharedGraphics::drawText(0, 0, "TIC TAC TOE", 1);
    
    if(!gameOver) {
        char turnText[20];
        sprintf(turnText, "PLAYER %c'S TURN", currentPlayer);
        SharedGraphics::drawText(20, 55, turnText, 1);
    }
    
    SharedGraphics::updateDisplay();
}

bool TicTacToeGame::isValidMove(int row, int col) {
    // Following your algorithm
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}

bool TicTacToeGame::checkWin(char player) {
    // Check rows and columns 
    for(int i = 0; i < 3; i++) {
        // Check rows
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
        // Check columns
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    
    // Check diagonals 
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }
    
    return false;
}

bool TicTacToeGame::checkDraw() {
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void TicTacToeGame::switchPlayer() {
    
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void TicTacToeGame::displayWinner() {
    char winText[20];
    sprintf(winText, "PLAYER %c WINS!", winner);
    SharedGraphics::drawText(20, 40, winText, 2);
    SharedGraphics::drawText(30, 55, "PRESS SELECT", 1);
}

void TicTacToeGame::displayDraw() {
    SharedGraphics::drawText(25, 40, "DRAW GAME!", 2);
    SharedGraphics::drawText(30, 55, "PRESS SELECT", 1);
}

void TicTacToeGame::drawGrid() {
    // Draw 3x3 grid
    int gridSize = 36;
    int startX = 30;
    int startY = 15;
    
    // Vertical lines
    SharedGraphics::drawLine(startX + gridSize, startY, startX + gridSize, startY + gridSize*3);
    SharedGraphics::drawLine(startX + gridSize*2, startY, startX + gridSize*2, startY + gridSize*3);
    
    // Horizontal lines
    SharedGraphics::drawLine(startX, startY + gridSize, startX + gridSize*3, startY + gridSize);
    SharedGraphics::drawLine(startX, startY + gridSize*2, startX + gridSize*3, startY + gridSize*2);
}

void TicTacToeGame::drawSymbol(int row, int col, char symbol) {
    int cellSize = 36;
    int startX = 30;
    int startY = 15;
    
    int centerX = startX + (col * cellSize) + (cellSize / 2);
    int centerY = startY + (row * cellSize) + (cellSize / 2);
    
    if(symbol == 'X') {
        // Draw X
        SharedGraphics::drawLine(centerX - 10, centerY - 10, centerX + 10, centerY + 10);
        SharedGraphics::drawLine(centerX + 10, centerY - 10, centerX - 10, centerY + 10);
    } else if(symbol == 'O') {
        // Draw O (circle)
        for(int i = 0; i < 360; i += 30) {
            int x1 = centerX + 10 * cos(i * 3.14 / 180);
            int y1 = centerY + 10 * sin(i * 3.14 / 180);
            int x2 = centerX + 10 * cos((i + 30) * 3.14 / 180);
            int y2 = centerY + 10 * sin((i + 30) * 3.14 / 180);
            SharedGraphics::drawLine(x1, y1, x2, y2);
        }
    }
}

void TicTacToeGame::drawCursor() {
    int cellSize = 36;
    int startX = 30;
    int startY = 15;
    
    int x = startX + (cursorCol * cellSize);
    int y = startY + (cursorRow * cellSize);
    
    // Draw blinking cursor rectangle
    if(millis() % 1000 < 500) {
        SharedGraphics::drawRect(x + 2, y + 2, cellSize - 4, cellSize - 4, false);
    }
}

void TicTacToeGame::cleanup() {
    gameOver = false;
}