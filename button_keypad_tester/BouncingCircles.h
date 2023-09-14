#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class BouncingCircles {
  private:
    Adafruit_SSD1306 *display;
    int numCircles;
    int *xPositions;
    int *yPositions;
    int *xVelocities;
    int *yVelocities;
    int circleRadius;
    int screenWidth;
    int screenHeight;

    void drawCircle(int x, int y) {
      display->drawCircle(x, y, circleRadius, WHITE);
    }

    void eraseCircle(int x, int y) {
      display->drawCircle(x, y, circleRadius, BLACK);
    }

    void updatePosition(int circleIndex) {
      int newX = xPositions[circleIndex] + xVelocities[circleIndex];
      int newY = yPositions[circleIndex] + yVelocities[circleIndex];

      // Bounce off edges of screen
      if (newX < circleRadius || newX > screenWidth - circleRadius) {
        xVelocities[circleIndex] = -xVelocities[circleIndex];
      }
      if (newY < circleRadius || newY > screenHeight - circleRadius) {
        yVelocities[circleIndex] = -yVelocities[circleIndex];
      }

      xPositions[circleIndex] = newX;
      yPositions[circleIndex] = newY;
    }

  public:
    BouncingCircles(Adafruit_SSD1306 *display, int numCircles, int circleRadius) {
      this->display = display;
      this->numCircles = numCircles;
      this->circleRadius = circleRadius;
      this->screenWidth = SCREEN_WIDTH;
      this->screenHeight = SCREEN_HEIGHT;
      this->xPositions = new int[numCircles];
      this->yPositions = new int[numCircles];
      this->xVelocities = new int[numCircles];
      this->yVelocities = new int[numCircles];

      // Initialize circle positions and velocities randomly
      for (int i = 0; i < numCircles; i++) {
        xPositions[i] = random(circleRadius, screenWidth - circleRadius);
        yPositions[i] = random(circleRadius, screenHeight - circleRadius);
        xVelocities[i] = random(-2, 2);
        yVelocities[i] = random(-2, 2);
      }
    }

    ~BouncingCircles() {
      delete[] xPositions;
      delete[] yPositions;
      delete[] xVelocities;
      delete[] yVelocities;
    }

    void update() {
      for (int i = 0; i < numCircles; i++) {
        eraseCircle(xPositions[i], yPositions[i]);
        updatePosition(i);
        drawCircle(xPositions[i], yPositions[i]);
      }
    }
};
