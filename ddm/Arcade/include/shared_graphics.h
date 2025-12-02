#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class SharedGraphics {
public:
    static void initialize();
    static void clearDisplay();
    static void drawPixel(int x, int y);
    static void drawRect(int x, int y, int w, int h, bool fill = false);
    static void drawText(int x, int y, const char* text, int size = 1);
    static void drawLine(int x0, int y0, int x1, int y1);
    static void updateDisplay();
    
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 64;
    
private:
    static Adafruit_SSD1306 display;
};