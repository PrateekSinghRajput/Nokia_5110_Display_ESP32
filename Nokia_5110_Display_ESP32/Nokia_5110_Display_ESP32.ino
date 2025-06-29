#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(18, 23, 19, 2, 15);

#define BUTTON_LEFT_UP  14
#define BUTTON_RIGHT_UP 27

const int paddleHeight = 12;
const int paddleWidth = 2;
const int ballSize = 4;
const int screenWidth = 84;
const int screenHeight = 48;

int paddleLeftY, paddleRightY;
int16_t ballX, ballY;
int8_t ballVX, ballVY;

int scoreLeft = 0;
int scoreRight = 0;

void setup() {

  display.begin();
  display.setContrast(60);
  display.clearDisplay();

  pinMode(BUTTON_LEFT_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_UP, INPUT_PULLUP);

  paddleLeftY = (screenHeight - paddleHeight) / 2;
  paddleRightY = (screenHeight - paddleHeight) / 2;

  ballX = screenWidth / 2;
  ballY = screenHeight / 2;
  ballVX = -1;
  ballVY = 1;

  drawGame();
}

void loop() {

  bool leftUpPressed = digitalRead(BUTTON_LEFT_UP) == LOW;
  bool rightUpPressed = digitalRead(BUTTON_RIGHT_UP) == LOW;

  if (leftUpPressed) {
    paddleLeftY -= 2;
  } else {
    paddleLeftY += 1;
  }
  if (rightUpPressed) {
    paddleRightY -= 2;
  } else {
    paddleRightY += 1;
  }

  paddleLeftY = constrain(paddleLeftY, 0, screenHeight - paddleHeight);
  paddleRightY = constrain(paddleRightY, 0, screenHeight - paddleHeight);


  ballX += ballVX;
  ballY += ballVY;

  if (ballY <= 0) {
    ballY = 0;
    ballVY = -ballVY;
  } else if (ballY >= screenHeight - ballSize) {
    ballY = screenHeight - ballSize;
    ballVY = -ballVY;
  }


  if (ballX <= paddleWidth) {
    if (ballY + ballSize >= paddleLeftY && ballY <= paddleLeftY + paddleHeight) {
      ballX = paddleWidth;  
      ballVX = -ballVX;
    } else if (ballX < 0) {
      scoreRight++;
      resetBall(-1);
    }
  }


  if (ballX >= screenWidth - paddleWidth - ballSize) {
    if (ballY + ballSize >= paddleRightY && ballY <= paddleRightY + paddleHeight) {
      ballX = screenWidth - paddleWidth - ballSize;
      ballVX = -ballVX;
    } else if (ballX > screenWidth - ballSize) {
      scoreLeft++;
      resetBall(1);
    }
  }

  drawGame();

  delay(30); 
}

void resetBall(int direction) {
  ballX = screenWidth / 2;
  ballY = screenHeight / 2;
  ballVX = direction; 
  ballVY = random(0, 2) == 0 ? 1 : -1;  
}

void drawGame() {
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10, 0);
  display.print("L:");
  display.print(scoreLeft);
  display.setCursor(screenWidth - 30, 0);
  display.print("R:");
  display.print(scoreRight);

  display.fillRect(0, paddleLeftY, paddleWidth, paddleHeight, BLACK);
  display.fillRect(screenWidth - paddleWidth, paddleRightY, paddleWidth, paddleHeight, BLACK);

  display.fillRect(ballX, ballY, ballSize, ballSize, BLACK);

  display.display();
}
