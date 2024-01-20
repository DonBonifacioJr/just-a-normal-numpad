#include "menuScreen.h"
#include "NewKeys.h"
//#include "macro.h"



int cursorPos = 0;
int cursorLimit = 3;
enum SubMenuState {MAIN, GAMES_SUB, MACRO_SUB, SUB_ERR};
long unsigned lastTimeSprite = 0;
long unsigned lastTimeNav = 0;
int navigateDelay = 65;
int spriteTime = 250;
bool spriteAnimState = false;
bool selectOptionButton = false;

SubMenuState currSubState = MAIN;
SubMenuState lastSubState = MAIN;

// User Input
NewKeys inputKey;

int mainSelect = 0, macroSelect = 0, gameSelect = 0;

void menuScreen (MenuState& currState, MenuState& lastState, int& subSelect, Adafruit_SSD1306& display) {
  display.clearDisplay();
  DisplayMenuLoopLabels(display);
  DisplayCursorLoop(display);

  if (millis() - lastTimeSprite >= spriteTime) {
    spriteAnimState = !spriteAnimState;
    lastTimeSprite = millis();
  }

  if (millis() - lastTimeNav >= navigateDelay) {
    MenuNavigator();
    lastTimeNav = millis();
  }

  optionSelector(currState, lastState, subSelect, display);
  
  display.display();

  selectOptionButton = false;

  
}

void DisplayMenuLoopLabels(Adafruit_SSD1306& display) {
  
  display.drawFastHLine(0, 18, 256, 1);
  display.drawFastHLine(0, 19, 256, 1);

  display.setCursor(84, 10);
  display.setTextSize(1);
  display.println("ANEMONE");
  switch(currSubState) {
    case MAIN:
      //display.invertDisplay(true);
      display.setCursor(4, 3);
      display.setTextSize(2);
      display.println("menu");
      
      display.setCursor(20, 22);
      display.setTextSize(1);
      display.println("keypad");
  
      display.setCursor(20, 32);
      display.println("macropad");

      display.setCursor(20, 42);
      display.println("wip");
   
      display.setCursor(20, 52);
      display.println("back<-");
      
      break;
    case MACRO_SUB:
      cursorLimit = 3;
      display.setCursor(4, 3);
      display.setTextSize(2);
      display.println("macro");
      
      display.setCursor(20, 22);
      display.setTextSize(1);
      display.println("twitch");
  
      display.setCursor(20, 32);
      display.println("music");

      display.setCursor(20, 42);
      display.println("procreate");
   
      display.setCursor(20, 52);
      display.println("back<-");
      break;
  }
    
}

void DisplayCursorLoop(Adafruit_SSD1306& display) {
  switch (currSubState) {
    case MAIN:
        switch(cursorPos) {
          case 0:
            if (!spriteAnimState) {
              display.drawBitmap(6, 21, epd_bitmap_Cursor, 8, 9, WHITE);
            // Icon image
              display.drawBitmap(82, 22, epd_bitmap_Keysprite, 40, 40, WHITE);
            }
            else {
              display.drawBitmap(3, 21, epd_bitmap_Cursor, 8, 9, WHITE);
              display.drawBitmap(82, 20, epd_bitmap_Keysprite, 40, 40, WHITE);
            }
            break;
          case 1:
            if (!spriteAnimState) {
              display.drawBitmap(6, 31, epd_bitmap_Cursor, 8, 9, WHITE);
              // Icon image
              display.drawBitmap(82, 22, epd_bitmap_Macromenu, 40, 40, WHITE);
            }
            else {
              display.drawBitmap(3, 31, epd_bitmap_Cursor, 8, 9, WHITE);
              display.drawBitmap(82, 20, epd_bitmap_Macromenu, 40, 40, WHITE);
            }
            break;
        case 2:
          if (!spriteAnimState) {
            display.drawBitmap(6, 41, epd_bitmap_Cursor, 8, 9, WHITE);
            // Icon image
            display.drawBitmap(82, 22, epd_bitmap_AmeIcon, 40, 40, WHITE);
          }
          else {
            display.drawBitmap(3, 41, epd_bitmap_Cursor, 8, 9, WHITE);
            display.drawBitmap(82, 20, epd_bitmap_AmeIcon, 40, 40, WHITE);
          }
          break;
        case 3:
          if (!spriteAnimState) {
            display.drawBitmap(6, 51, epd_bitmap_Cursor, 8, 9, WHITE);
            // Icon image
            //display.drawBitmap(82, 22, epd_bitmap_Backarrow, 40, 40, WHITE);
        
          }
          else {
           display.drawBitmap(3, 51, epd_bitmap_Cursor, 8, 9, WHITE);
           //display.drawBitmap(82, 20, epd_bitmap_Backarrow, 40, 40, WHITE);
        
          }
          break;
        default:
          break;
        }
      break;
    case MACRO_SUB:
        switch(cursorPos) {
          case 0:
            if (!spriteAnimState) {
              display.drawBitmap(6, 21, epd_bitmap_Cursor, 8, 9, WHITE);
            // Icon image
              display.drawBitmap(82, 22, epd_bitmap_AmeIcon, 40, 40, WHITE);
            }
            else {
              display.drawBitmap(3, 21, epd_bitmap_Cursor, 8, 9, WHITE);
              display.drawBitmap(82, 20, epd_bitmap_AmeIcon, 40, 40, WHITE);
            }
            break;
          case 1:
            if (!spriteAnimState) {
              display.drawBitmap(6, 31, epd_bitmap_Cursor, 8, 9, WHITE);
              // Icon image
              display.drawBitmap(82, 22, epd_bitmap_MusicIcon, 40, 40, WHITE);
            }
            else {
              display.drawBitmap(3, 31, epd_bitmap_Cursor, 8, 9, WHITE);
              display.drawBitmap(82, 20, epd_bitmap_MusicIcon, 40, 40, WHITE);
            }
            break;
        case 2:
          if (!spriteAnimState) {
            display.drawBitmap(6, 41, epd_bitmap_Cursor, 8, 9, WHITE);
            // Icon image
            display.drawBitmap(82, 22, epd_bitmap_TakoIcon, 40, 40, WHITE);
          }
          else {
            display.drawBitmap(3, 41, epd_bitmap_Cursor, 8, 9, WHITE);
            display.drawBitmap(82, 20, epd_bitmap_TakoIcon, 40, 40, WHITE);
          }
          break;
        case 3:
          if (!spriteAnimState) {
            display.drawBitmap(6, 51, epd_bitmap_Cursor, 8, 9, WHITE);
            // Icon image
            //display.drawBitmap(82, 22, epd_bitmap_Backarrow, 40, 40, WHITE);
        
          }
          else {
           display.drawBitmap(3, 51, epd_bitmap_Cursor, 8, 9, WHITE);
           //display.drawBitmap(82, 20, epd_bitmap_Backarrow, 40, 40, WHITE);
        
          }
          break;
        default:
          break;
        }
    break;
      }
}

void MenuNavigator() {
  int userInput = inputKey.readInput();
  if (userInput == 56) {
   if (cursorPos == cursorLimit) {
    cursorPos = 0;
   }
   else {
    cursorPos++;
   }
  }
  else if (userInput == 50) {
    if (cursorPos == 0) {
      cursorPos = cursorLimit;
    }
    else {
      cursorPos--;
    }
  }
  else if (userInput == 53) {
    selectOptionButton = true;
  }
  else {
    selectOptionButton = false;
  }
}

void optionSelector (MenuState& currState, MenuState lastState, int& subSelect, Adafruit_SSD1306& display) {
  switch (currSubState) {
    case MAIN:
      switch (cursorPos) {
        case 0:
          if (selectOptionButton == true) {
            currState = KEYPAD;
            selectOptionButton = false;
          }
          break;
        case 1:
          if (selectOptionButton == true) {
            currState = MENUOPEN;
            currSubState = MACRO_SUB;
            lastSubState = MAIN;
            
            selectOptionButton = false;
            cursorPos = 0;
            delay(90);
          }
          break;
        case 2:
          if (selectOptionButton == true) {
            currState = KEYPAD;
            selectOptionButton = false;
          }
          break;
        case 3:
          if (selectOptionButton == true) {
            currState = lastState;
            selectOptionButton = false;
            subSelect = 0;
            display.clearDisplay();
          }
          break;
        default:
          break;
      }
      break;
    case MACRO_SUB:
      switch (cursorPos) {
        case 0:
          if (selectOptionButton == true) {
            selectOptionButton = false;
            delay(90);
            cursorPos = 0;
            subSelect = 0;
            currState = MACRO;
            display.clearDisplay();
            display.display();
          }
          break;
        case 1:
          if (selectOptionButton == true) {
            selectOptionButton = false;
            delay(90);
            cursorPos = 0;
            subSelect = 1;
            currState = MACRO;
            display.clearDisplay();
            display.display();
          }
          break;
        case 2:
          if (selectOptionButton == true) {
            selectOptionButton = false;
            delay(90);
            cursorPos = 0;
            subSelect = 2;
            currState = MACRO;
            display.clearDisplay();
            display.display();
          }
          break;
        case 3:
          if (selectOptionButton == true) {
            currSubState = lastSubState;
            lastSubState = MACRO_SUB;
            selectOptionButton = false;
            delay(90);
            cursorPos = 0;
            //display.clearDisplay();
          }
          break;
        default:
          break;
      }
  }
}
