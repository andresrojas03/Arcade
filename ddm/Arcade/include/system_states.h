#pragma once

enum SystemState {
    STATE_BOOT,
    STATE_MENU,
    STATE_GAME_SELECTED, 
    STATE_GAME_RUNNING,
    STATE_GAME_PAUSED,
    STATE_GAME_OVER,
    STATE_SHUTDOWN
};

enum GameType {
    GAME_SNAKE = 0,
    GAME_PONG,
    GAME_TICTACTOE,
    NO_GAME = -1
};