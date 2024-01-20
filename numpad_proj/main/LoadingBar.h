#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>

class LoadingBar {
  private:
    //Adafruit_SSD1306 display;
    int loadingBarWidth;
    int loadingBarX;
    int loadingBarY;
    int loadingBarHeight;
    int loadingPercentage;
    bool loadingComplete;

  public:
    LoadingBar() :
      //display(128, 64, &Wire, -1) // SSD1306 display dimensions
      loadingBarWidth(90) // width of loading bar
    {
      loadingBarX = 18; // x coordinate of loading bar
      loadingBarY = 20; // y coordinate of loading bar
      loadingBarHeight = 4; // height of loading bar
      loadingPercentage = 0; // initial loading percentage
      loadingComplete = false; // loading is not yet complete
    }
    
    ~LoadingBar() {
      display.clearDisplay(); // clear display when the object is destroyed
    }

//    void setup() {
//      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize display
//      if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
//        Serial.println(F("SSD1306 allocation failed"));
//        for (;;); // Don't proceed, loop forever
//      }
//    }

    void renderLoad() {
      display.clearDisplay();

      display.setTextSize(2); // set text size
      display.setTextColor(WHITE); // set text color
      display.setCursor(22, 28); // set text cursor
      display.println("anemone"); // display loading text

      display.drawRect(loadingBarX - 1, loadingBarY - 1, loadingBarWidth + 2, loadingBarHeight + 2, WHITE); // draw loading bar border

      // Draw loading bar with increasing width using for loop
      for (int i = 0; i <= 100; i += 2) {
        display.fillRect(loadingBarX, loadingBarY, i * loadingBarWidth / 100, loadingBarHeight, WHITE); // draw loading bar
        display.display(); // display frame
        delay(15); // pause to control animation speed
      }
      delay(90);

      loadingComplete = true; // loading is now complete
      display.clearDisplay(); // clear screen
 /*
      display.setCursor(14, 26); // set text cursor
      display.println("by semi7"); // display startup complete text
      display.display(); // display frame
      delay(1000);
      display.clearDisplay();
      display.display(); // display frame
*/
      display.display();
      delay(100);
    }

    void deletion() {
      if (loadingComplete) {
        delete this;
      }
    }
};
