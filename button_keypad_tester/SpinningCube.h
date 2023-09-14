#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

class SpinningCube {
  private:
    Adafruit_SSD1306 display;
    int centerX;
    int centerY;
    int cubeSize;
    int cubeSpeed;
    unsigned long prevMillis;
    unsigned long currMillis;
    int currentAngle;

  public:
    SpinningCube() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {
      centerX = SCREEN_WIDTH / 2;
      centerY = SCREEN_HEIGHT / 2;
      cubeSize = 20;
      cubeSpeed = 2;
      prevMillis = 0;
      currMillis = 0;
      currentAngle = 0;
    }

    void setup() {
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
      display.clearDisplay();
      display.display();
    }

    void draw() {
      currMillis = millis();
      if (currMillis - prevMillis > cubeSpeed) {
        prevMillis = currMillis;
        display.clearDisplay();
        display.drawRect(centerX - cubeSize, centerY - cubeSize, 2 * cubeSize, 2 * cubeSize, WHITE);
        display.drawLine(centerX - cubeSize, centerY - cubeSize, centerX - cubeSize / 2, centerY - cubeSize / 2, WHITE);
        display.drawLine(centerX + cubeSize, centerY - cubeSize, centerX + cubeSize / 2, centerY - cubeSize / 2, WHITE);
        display.drawLine(centerX - cubeSize, centerY + cubeSize, centerX - cubeSize / 2, centerY + cubeSize / 2, WHITE);
        display.drawLine(centerX + cubeSize, centerY + cubeSize, centerX + cubeSize / 2, centerY + cubeSize / 2, WHITE);
        display.drawLine(centerX - cubeSize / 2, centerY - cubeSize / 2, centerX + cubeSize / 2, centerY - cubeSize / 2, WHITE);
        display.drawLine(centerX + cubeSize / 2, centerY - cubeSize / 2, centerX + cubeSize / 2, centerY + cubeSize / 2, WHITE);
        display.drawLine(centerX + cubeSize / 2, centerY + cubeSize / 2, centerX - cubeSize / 2, centerY + cubeSize / 2, WHITE);
        display.drawLine(centerX - cubeSize / 2, centerY + cubeSize / 2, centerX - cubeSize / 2, centerY - cubeSize / 2, WHITE);
        currentAngle = (currentAngle + 5) % 360;
        display.setRotation(currentAngle / 45);
        display.display();
      }
    }
};
