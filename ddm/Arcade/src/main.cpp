#include <Arduino.h>
#include "arcade_system.h"

ArcadeSystem arcade;

void setup() {
    arcade.initialize();
}

void loop() {
    arcade.run();
    delay(50); // ~20 FPS for responsive menu
}