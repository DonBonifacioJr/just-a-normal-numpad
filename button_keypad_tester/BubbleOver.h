#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
#include "bitmaps.h"
#include "RandomBetweenRanges.h"
//#include "NewKeys.h"
//#include "SingleKey.h"

//SingleKey key;

class BubbleOver {
  private:
    //Adafruit_SSD1306 display;
    int numCircles;
    int circleX[10], circleY[10], circleRadius[10];
    long unsigned lastTime = 0;
    int bubbleDelay = 50;
    

  public:
    BubbleOver():
    numCircles(4)// number of circles to draw
      {
      for (int i = 0; i < numCircles; i++) {
        circleX[i] = generateRandomNumber(0, 128, 34, 94); // random x coordinate
        circleY[i] = 32; // initial y coordinate at bottom of screen
        circleRadius[i] = random(4, 10); // random radius between 2 and 5
      }
      //display(128, 64, &Wire, -1) // SSD1306 display dimensions
    }

    ~BubbleOver() {
      display.clearDisplay(); // clear display when the object is destroyed
    }

    void setup() {
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize display
      if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
      }

      display.clearDisplay();
    }

    void loop(char lastKey) {
      long unsigned currTime = millis();
      if (currTime - lastTime > bubbleDelay) {
        display.clearDisplay(); // clear previous frame
        //display.drawBitmap(0, 0, epd_bitmap_bocchi128x64, 128, 64, WHITE);
        display.setTextSize(3); // set text size
        display.setTextColor(WHITE); // set text color
        display.setCursor(58, 26); // set text cursor
        display.println(lastKey); // display loading text
//        if (key.getKeyHold1() == 1) {
//          numCircles = 4;
//        }
        for (int i = 0; i < numCircles; i++) {
          display.drawCircle(circleX[i], circleY[i], circleRadius[i], WHITE); // draw circle
          circleY[i] -= ((random(1, 4) * circleRadius[i]) / 8); // move circle up by random amount
          if (circleY[i] + circleRadius[i] <= 0) { // if circle is off screen
            circleX[i] = generateRandomNumber(0, 128, 34, 94); // reset x coordinate to random value
            circleY[i] = 64; // reset y coordinate to bottom of screen
            circleRadius[i] = random(8, 18); // reset radius to random value
          }
        }
        numCircles = 4;
        display.display(); // display frame
        lastTime = currTime;
        //delay(50); // pause to control animation speed
      }
      
    }
    
    void deletion() {
      delete this;
    }

    int getBubbleDelay() {
      return bubbleDelay;
    }
};
