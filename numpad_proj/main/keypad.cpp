#include "keypad.h"
#include "RandomBetweenRanges.h"
#include "MenuState.h"

// Display Bubbles
int numCircles = 4;
int circleX[10], circleY[10], circleRadius[10];
long unsigned lastTime = 0;
int bubbleDelay = 65;
String myMessage = " ";
int formatNum = 0;
bool setupStatus = false;
char oldKey = '0';


// Keyboard
NewKeys key;

void keypad(MenuState& currState, Adafruit_SSD1306& display) {
  if (!setupStatus) {
    for (int i = 0; i < numCircles; i++) {
      circleX[i] = generateRandomNumber(0, 128, 34, 94); // random x coordinate
      circleY[i] = 32; // initial y coordinate at bottom of screen
      circleRadius[i] = random(4, 10); // random radius between 2 and 5
    }
    setupStatus = true;
  }

  keypadChange(key, display);
  key.readKey();
  
  char lastKey = key.getLastKey();
  if (lastKey != oldKey) {
    formatNum = 0;
    myMessage = String(lastKey);
    oldKey = lastKey;
  }

  DisplayKeysLoop(display);
}

void DisplayKeysLoop(Adafruit_SSD1306& display) {
  long unsigned currTime = millis();
  if (currTime - lastTime > bubbleDelay) {
    display.clearDisplay(); // clear previous frame
    //display.drawBitmap(0, 0, epd_bitmap_bocchi128x64, 128, 64, WHITE);
    printKeysFormat(display);
    printKeysMessage(display); // display loading text
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

void printKeysFormat(Adafruit_SSD1306& display) {
  switch (formatNum) {
    case 0:
      display.setTextSize(3); // set text size
      display.setTextColor(WHITE); // set text color
      display.setCursor(58, 26); // set text cursor
      break;
    case 1:
      display.setTextSize(2); // set text size
      display.setTextColor(WHITE); // set text color
      display.setCursor(6, 26); // set text cursor
      break;
    default:
      display.setTextSize(3); // set text size
      display.setTextColor(WHITE); // set text color
      display.setCursor(58, 26); // set text cursor
      break;
  }
}

void printKeysMessage(Adafruit_SSD1306& display) {
  display.println(myMessage);
}

int buttonPin = 16;  // Change this to the pin where your button is connected
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastKeyChangeDebounceTime = 0;
unsigned long lastKCPressTime = 0;
unsigned long debounceKeyChangeDelay = 50;  // Adjust this debounce delay as needed
unsigned long timeBetweenPresses = 500;  // Set the desired time window between consecutive presses


void keypadChange(NewKeys& keys, Adafruit_SSD1306& display) {
  int currKeyboard = keys.getKeyboard();
  int reading = digitalRead(buttonPin);
  Serial.println(reading);

  if (reading != lastButtonState) {
    lastKeyChangeDebounceTime = millis();
  }

  if ((millis() - lastKeyChangeDebounceTime) > debounceKeyChangeDelay) {
    if (reading != buttonState) {
      buttonState = reading;

       if (buttonState == LOW) {
        // Button has been pressed

        // Check if it's within the time window since the last press
        if ((millis() - lastKCPressTime) <= timeBetweenPresses) {
          // Button pressed twice within the time window
          Serial.println("Keys Changed");
          myMessage = "Key Change";
          formatNum = 1;
          printKeysFormat(display);
          printKeysMessage(display);

          if (currKeyboard == 3) {
            currKeyboard = 0;
            keys.setKeyboard(0);
          }
          else {
            currKeyboard += 1;
            keys.setKeyboard(currKeyboard);
          }
          keys.single_key_switcher();
        }
        lastKCPressTime = millis();  // Reset the debounce time
      }
    }
  }
  lastButtonState = reading;
}
  
