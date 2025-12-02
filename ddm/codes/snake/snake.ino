#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Optimized memory usage
#define MAX_SNAKE_LENGTH 30
#define GRID_SIZE 4

// Direction constants
#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

// Game variables
int direction = RIGHT;
int snakeLength = 3;
int fruitX, fruitY;
bool gameRunning = true;

// Snake segments
int snakeX[MAX_SNAKE_LENGTH];
int snakeY[MAX_SNAKE_LENGTH];

unsigned long lastUpdate = 0;
int gameSpeed = 200;

void generateFruit();

void setup() {
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  // Initialize snake starting position
  snakeX[0] = 64; // head
  snakeY[0] = 32;
  snakeX[1] = 60; // body
  snakeY[1] = 32;
  snakeX[2] = 56; // tail
  snakeY[2] = 32;
  
  generateFruit();
  
  display.clearDisplay();
  display.display();
  
  Serial.println("Snake Game Ready!");
}

void loop() {
  if (!gameRunning) {
    gameOver();
    return;
  }
  
  if (millis() - lastUpdate > gameSpeed) {
    lastUpdate = millis();
    updateGame();
    drawGame();
  }
}

void updateGame() {
  // Save new head position
  int newHeadX = snakeX[0];
  int newHeadY = snakeY[0];
  
  // Move based on direction
  switch(direction) {
    case RIGHT: newHeadX += GRID_SIZE; break;
    case LEFT:  newHeadX -= GRID_SIZE; break;
    case UP:    newHeadY -= GRID_SIZE; break;
    case DOWN:  newHeadY += GRID_SIZE; break;
  }
  
  // Screen wrapping
  if (newHeadX >= SCREEN_WIDTH) newHeadX = 0;
  if (newHeadX < 0) newHeadX = SCREEN_WIDTH - GRID_SIZE;
  if (newHeadY >= SCREEN_HEIGHT) newHeadY = 0;
  if (newHeadY < 0) newHeadY = SCREEN_HEIGHT - GRID_SIZE;
  
  // Check collision with self
  for (int i = 0; i < snakeLength; i++) {
    if (snakeX[i] == newHeadX && snakeY[i] == newHeadY) {
      gameRunning = false;
      return;
    }
  }
  
  // Move snake body
  for (int i = snakeLength; i > 0; i--) {
    snakeX[i] = snakeX[i-1];
    snakeY[i] = snakeY[i-1];
  }
  
  // Update head position
  snakeX[0] = newHeadX;
  snakeY[0] = newHeadY;
  
  // Check if snake ate fruit
  if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
    snakeLength++;
    if (snakeLength >= MAX_SNAKE_LENGTH) {
      snakeLength = MAX_SNAKE_LENGTH; // Prevent overflow
    }
    generateFruit();
    
    // Change direction randomly for testing
    direction = random(0, 4);
    
    // Increase speed slightly
    if (gameSpeed > 50) {
      gameSpeed -= 5;
    }
  }
}

void generateFruit() {
  bool validPosition = false;
  int attempts = 0;
  
  // Define safe margins
  int marginTop = 12;    // Avoid score area
  int marginBottom = 4;  // Small bottom margin
  int marginSides = 4;   // Small side margins
  
  while (!validPosition && attempts < 100) {
    fruitX = (random(marginSides / GRID_SIZE, (SCREEN_WIDTH - marginSides) / GRID_SIZE)) * GRID_SIZE;
    fruitY = (random(marginTop / GRID_SIZE, (SCREEN_HEIGHT - marginBottom) / GRID_SIZE)) * GRID_SIZE;
    
    validPosition = true;
    // Check if fruit doesn't overlap with snake
    for (int i = 0; i < snakeLength; i++) {
      if (snakeX[i] == fruitX && snakeY[i] == fruitY) {
        validPosition = false;
        break;
      }
    }
    attempts++;
  }
}

void drawGame() {
  display.clearDisplay();
  
  // Draw game elements
  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i], snakeY[i], GRID_SIZE, GRID_SIZE, SSD1306_WHITE);
  }
  display.fillRect(fruitX, fruitY, GRID_SIZE, GRID_SIZE, SSD1306_WHITE);
  
  // Score with trailing space to clear any artifacts
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.print(snakeLength - 3);
  display.print("  ");  // Add spaces to clear any leftover characters
  
  display.display();
}

void gameOver() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.println("GAME OVER");
  display.setTextSize(1);
  display.setCursor(40, 45);
  display.print("Score: ");
  display.print(snakeLength - 3);
  display.display();
  
  delay(3000);
  
  // Reset game
  resetGame();
}

void resetGame() {
  snakeLength = 3;
  snakeX[0] = 64;
  snakeY[0] = 32;
  snakeX[1] = 60;
  snakeY[1] = 32;
  snakeX[2] = 56;
  snakeY[2] = 32;
  direction = RIGHT;
  gameRunning = true;
  gameSpeed = 200;
  generateFruit();
}