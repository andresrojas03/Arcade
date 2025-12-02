#pragma once

class SharedInput {
public:
    enum Button {
        UP = 0,
        DOWN,
        LEFT, 
        RIGHT,
        SELECT,
        DENY,
        NONE
    };
    
    static void initialize();
    static Button getButton();
    static void update();
    
private:
    static const int BUTTON_UP_PIN = 2;
    static const int BUTTON_DOWN_PIN = 3;
    static const int BUTTON_LEFT_PIN = 4;
    static const int BUTTON_RIGHT_PIN = 5;
    static const int BUTTON_SELECT_PIN = 6;
    static const int BUTTON_DENY_PIN = 7;
    
    static unsigned long lastDebounceTime;
    static const unsigned long DEBOUNCE_DELAY = 50;
};