#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>



class BubblingCircles {
  private:
    Adafruit_SSD1306 display;
    int circleX, circleY, circleRadius;

  public:
  BubblingCircles() :
      display(128, 64, &Wire, -1) // SSD1306 display dimensions
    {
      circleX = 64; // initial x coordinate of circle
      circleY = 32; // initial y coordinate of circle
      circleRadius = 1; // initial radius of circle
    }

    
    void begin() {
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize display
      if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
          Serial.println(F("SSD1306 allocation failed"));
          for(;;); // Don't proceed, loop forever
      }
      
      display.clearDisplay();
    }

    void loop() {
      display.clearDisplay(); // clear previous frame
      display.drawCircle(circleX, circleY, circleRadius, WHITE); // draw circle
      circleY -= 1; // move circle up
      circleRadius += 1; // increase radius
      if (circleY + circleRadius <= 0) { // if circle is off screen
        circleY = 32; // reset y coordinate to bottom of screen
        circleRadius = 1; // reset radius
      }
      display.display(); // display frame
      delay(50); // pause to control animation speed
    }
};
