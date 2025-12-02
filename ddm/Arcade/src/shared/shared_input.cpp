#include "shared_input.h"
#include <Arduino.h>

unsigned long SharedInput::lastDebounceTime = 0;

void SharedInput::initialize() {
    pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
    pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);
    pinMode(BUTTON_DENY_PIN, INPUT_PULLUP);
}

SharedInput::Button SharedInput::getButton() {
    if(digitalRead(BUTTON_UP_PIN) == LOW) return UP;
    if(digitalRead(BUTTON_DOWN_PIN) == LOW) return DOWN;
    if(digitalRead(BUTTON_LEFT_PIN) == LOW) return LEFT;
    if(digitalRead(BUTTON_RIGHT_PIN) == LOW) return RIGHT;
    if(digitalRead(BUTTON_SELECT_PIN) == LOW) return SELECT;
    if(digitalRead(BUTTON_DENY_PIN) == LOW) return DENY;
    
    return NONE;
}

void SharedInput::update() {
    // Debounce logic can be added here
}