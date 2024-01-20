#include "macro.h"

// Input keys
NewKeys macroKeys;
//macroKeys.setKeyboard(0);
//macroKeys.single_key_switcher();

void macro(MenuState& currState, int& subSelect, Adafruit_SSD1306& display) {
  //display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE); // set text color
  macroOutputLoop (subSelect, display);
  macroIconLoop(subSelect, display);
  //macroChange(subSelect, display);
  
  display.display();
}

// Print icon indicators
void macroIconLoop (int subSelect, Adafruit_SSD1306& display) {
  switch (subSelect) {
    case 0:
      display.drawBitmap(44, 2, epd_bitmap_AmeIcon, 40, 40, WHITE);
      break;
    case 1:
      display.drawBitmap(44, 2, epd_bitmap_MusicIcon, 40, 40, WHITE);
      break;
    case 2:
      display.drawBitmap(44, 2, epd_bitmap_TakoIcon, 40, 40, WHITE);
      break;
    default:
      display.drawBitmap(44, 2, epd_bitmap_MusicIcon, 40, 40, WHITE);
      break;
    
  }
}

void macroOutputLoop (int subSelect, Adafruit_SSD1306& display) {
  int num =  macroKeys.readInput();
  switch (subSelect) {
    case 0:
      genMacros(num, display);
      break;
    case 1:
      musicMacros(num, display);
      break;
    case 2:
      artMacros(num, display); 
      break;
  }
  
}

void genMacros(int num, Adafruit_SSD1306& display) {
  switch(num) {
    case 49:
      Keyboard.print("OMEGALUL ");
      display.clearDisplay();
      display.setCursor(16, 48); // set text cursor
      display.println("OMEGALUL");
      delay(80);
      break;
    case 50:
      Keyboard.print("KEKW ");
      display.clearDisplay();
      display.setCursor(40, 48); // set text cursor
      display.println("KEKW");
      delay(80);
      break;
    case 51:
      Keyboard.print("LULW ");
      display.clearDisplay();
      display.setCursor(40, 48); // set text cursor
      display.println("LULW");
      delay(80);
      break;
    case 52:
      Keyboard.print("PogChamp ");
      display.clearDisplay();
      display.setCursor(18, 48); // set text cursor
      display.println("PogChamp");
      delay(80);
      break;
    case 53:
      Keyboard.print("Sadge ");
      display.clearDisplay();
      display.setCursor(36, 48); // set text cursor
      display.println("Sadge");
      delay(80);
      break;
    case 54:
      Keyboard.print("3Head ");
      display.clearDisplay();
      display.setCursor(36, 48); // set text cursor
      display.println("3Head");
      delay(80);
      break;
    case 55:
      Keyboard.print("FeelsBadMan ");
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(0, 48); // set text cursor
      display.println("FeelsBadMan");
      delay(80);
      break;
    case 56:
      Keyboard.print("POGGERS ");
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(24, 48); // set text cursor
      display.println("POGGERS");
      delay(80);
      break;
    case 57:
      Keyboard.press(KEY_ENTER);
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(36, 48); // set text cursor
      display.println("enter");
      delay(80);
      break;
  }
}

void musicMacros(int num, Adafruit_SSD1306& display) { 
  switch(num) {
    case 49:
      Consumer.write(MEDIA_VOLUME_DOWN);
      display.clearDisplay();
      display.setTextColor(WHITE); // set text color
      display.setCursor(12, 48); // set text cursor
      display.println("vol. dwn");
      delay(80);
      break;
    case 50:
      Consumer.write(MEDIA_VOLUME_MUTE);
      display.clearDisplay();
      display.setCursor(42, 48); // set text cursor
      display.println("mute");
      delay(80);
      break;
    case 51:
      Consumer.write( MEDIA_VOLUME_UP);
      display.clearDisplay();
      display.setCursor(18, 48); // set text cursor
      display.println("vol. up");
      delay(80);
      break;
    case 52:
      Consumer.write(MEDIA_PREVIOUS);
      display.clearDisplay();
      display.setCursor(38, 48); // set text cursor
      display.println("prev.");
      delay(80);
      break;
    case 53:
      Consumer.write(MEDIA_PLAY_PAUSE);
      display.clearDisplay();
      display.setCursor(34, 48); // set text cursor
      display.println("pause");
      delay(80);
      break;
    case 54:
      Consumer.write(MEDIA_NEXT);
      display.clearDisplay();
      display.setCursor(39, 48); // set text cursor
      display.println("next");
      delay(80);
      break;
    case 55:
      Consumer.write(MEDIA_REWIND);
      display.clearDisplay();
      display.setCursor(30, 48); // set text cursor
      display.println("rewind");
      delay(80);
      break;
    case 56:
      Consumer.write( MEDIA_FAST_FORWARD);
      display.clearDisplay();
      display.setCursor(48, 48); // set text cursor
      display.println("ff");
      delay(80);
      break;
    case 57:
      Consumer.write(MEDIA_STOP);
      display.clearDisplay();
      display.setCursor(39, 48); // set text cursor
      display.println("stop");
      delay(80);
      break;
    default:
      break;
  }
}


void artMacros(int num, Adafruit_SSD1306& display) {
  switch(num) {
    case 49:
      Keyboard.press(KEY_LEFT_WINDOWS);
      Keyboard.press('z');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(42, 48); // set text cursor
      display.println("undo");
      delay(80);
      break;
    case 50:
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_LEFT_WINDOWS);
      Keyboard.press('z');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(42, 48); // set text cursor
      display.println("redo");
      delay(80);
      break;
      break;
    case 51:
      Keyboard.press('e');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(36, 48); // set text cursor
      display.println("erase");
      delay(80);
      break;
    case 52:
      Keyboard.press('l');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(28, 48); // set text cursor
      display.println("layers");
      delay(80);
      break;
    case 53:
      Keyboard.press('s');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(28, 48); // set text cursor
      display.println("select");
      delay(80);
      break;
    case 54:
      Keyboard.press('b');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(34, 48); // set text cursor
      display.println("brush");
      delay(80);
      break;
    case 55:
      Keyboard.press('v');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(2, 38); // set text cursor
      display.println("transform");
      delay(80);
      break;
    case 56:
      Keyboard.press('c');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(36, 28); // set text cursor
      display.println("color");
      delay(80);
      break;
    case 57:
      Keyboard.press(' ');
      Keyboard.releaseAll();
      display.clearDisplay();
      display.setCursor(42, 28); // set text cursor
      display.println("menu");
      delay(80);
      break;
  }
}

/*

int buttonPinM = 16;  // Change this to the pin where your button is connected
int buttonStateM = HIGH;
int lastButtonStateM = HIGH;
unsigned long lastMacroChangeDebounceTime = 0;
unsigned long lastMCPressTime = 0;
unsigned long debounceMacroChangeDelay = 50;  // Adjust this debounce delay as needed
//unsigned long timeBetweenPresses = 500;  // Set the desired time window between consecutive presses

void macroChange(int& subSelect, Adafruit_SSD1306& display) {
  int reading = digitalRead(buttonPinM);

  if (reading != lastButtonStateM) {
    lastMacroChangeDebounceTime = millis();
  }

  if ((millis() - lastMacroChangeDebounceTime) > debounceMacroChangeDelay) {
    if (reading != buttonStateM) {
      buttonStateM = reading;

       if (buttonStateM == LOW) {
        // Button has been pressed

        // Check if it's within the time window since the last press
        if ((millis() - lastMCPressTime) <= 500) {
          // Button pressed twice within the time window
          Serial.println("Macros Changed");
          display.clearDisplay();
          display.setTextSize(2); // set text size
          display.setTextColor(WHITE); // set text color
          display.invertDisplay(true);
          display.setCursor(34, 14); // set text cursor
          display.println("Macro");
          display.setCursor(22, 29);
          display.println("Changed");
          display.display();
          delay(1550);
          display.invertDisplay(false);
          display.clearDisplay();

          if (subSelect == 2) {
            subSelect = 0;
          }
          else {
            subSelect++;
          }
          Serial.println(subSelect);
        }
        lastMCPressTime = millis();  // Reset the debounce time
      }
    }
  }
  lastButtonStateM = reading;
}

*/
