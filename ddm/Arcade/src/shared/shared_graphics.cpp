#include "shared_graphics.h"

Adafruit_SSD1306 SharedGraphics::display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void SharedGraphics::initialize() {
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for(;;); // Hang if display fails
    }
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
}

void SharedGraphics::clearDisplay() {
    display.clearDisplay();
}

void SharedGraphics::drawPixel(int x, int y) {
    display.drawPixel(x, y, SSD1306_WHITE);
}

void SharedGraphics::drawRect(int x, int y, int w, int h, bool fill) {
    if(fill) {
        display.fillRect(x, y, w, h, SSD1306_WHITE);
    } else {
        display.drawRect(x, y, w, h, SSD1306_WHITE);
    }
}

void SharedGraphics::drawText(int x, int y, const char* text, int size) {
    display.setTextSize(size);
    display.setCursor(x, y);
    display.print(text);
}

void SharedGraphics::drawLine(int x0, int y0, int x1, int y1){
    display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);
}

void SharedGraphics::updateDisplay() {
    display.display();
}