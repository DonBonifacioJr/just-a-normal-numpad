#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
//#include "BubbleOver.h"
//#include "SingleKey.h"

class Menu {
  private:
    Adafruit_SSD1306 display;
    int selectedOption;
    int numOptions;
    //const char** optionLabels;
    bool menuOpen;
    const int buttonPin;
    const int debounceDelay;
    unsigned long lastDebounceTime;

  public:
    Menu(String* labels, int numLabels, int buttonPin, int debounceDelay) :
      display(128, 64, &Wire, -1), // SSD1306 display dimensions
      selectedOption(0),
      numOptions(numLabels),
      menuOpen(false),
      buttonPin(buttonPin),
      debounceDelay(debounceDelay),
      lastDebounceTime(0)
    {}

    ~Menu() {
      display.clearDisplay(); // clear display when the object is destroyed
    }

    void setup() {
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize display
      display.clearDisplay();
      pinMode(buttonPin, INPUT); // set button pin as input with pullup resistor
    }

    void loop(int menuState, int lastMenuState) {
      if (menuState == 1) {
        if (lastMenuState == 0) {
          display.clearDisplay();
          selectedOption = 0;
        }
        // Check button state and debounce
        int buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH && (millis() - lastDebounceTime) > debounceDelay) {
          menuOpen = true;
          selectedOption = 0;
        }
        lastDebounceTime = millis();
      } else {
        // Handle menu selection
        int buttonState = digitalRead(buttonPin);
        if (buttonState == HIGH && (millis() - lastDebounceTime) > debounceDelay) {
          // Button pressed, select next option
          selectedOption = (selectedOption + 1) % numOptions;
        }

        // Draw menu screen
        display.clearDisplay();
        display.setTextSize(2); // set text size
        display.setTextColor(WHITE); // set text color

        // Draw menu options
        for (int i = 0; i < numOptions; i++) {
          if (i == selectedOption) {
            display.println("> "); // prefix selected option with arrow
          } else {
            display.println("  "); // prefix unselected options with space
          }
          display.println(optionLabels[i]); // draw option label
        }

        display.display(); // display frame

        // Check if an option has been selected
        if (buttonState == HIGH && selectedOption >= 0 && selectedOption < numOptions) {
          menuOpen = false;
          display.clearDisplay(); // clear screen
          // Call the function corresponding to the selected option (placeholder for now)
          switch(selectedOption) {
            case 0:
              funct1();
              break;
            case 1:
              drawShape2();
              break;
            case 2:
              drawShape3();
              break;
            // Add more cases for additional options as needed
            default:
              // No action for invalid options
              break;
          }
        }
      }
    }

    // Placeholder functions for the selectable options
    void funct1() {
      BubbleOver bubble;
      deletion();
      bubble.setup();
      bubble.loop();
    }

    void drawShape2() {
      // Draw shape 2
    }

    void drawShape3() {
      // Draw shape 3
    }
    void deletion() {
        delete this;
    }
};
