#include "menu.h"
#include "keypad.h"
#include "MenuState.h"
#include "MenuScreen.h"
#include "macro.h"



void Menu (MenuState& currState, MenuState& lastState, int& subSelect, Adafruit_SSD1306& display) {
  switch(currState) {
    case KEYPAD:
      keypad(currState, display);
      break;
    case MENUOPEN:
      menuScreen(currState, lastState, subSelect, display);
      break;
    case ACTIVITY:
      break;
    case MACRO:
      macro(currState, subSelect, display);
      break;
    case ERR:
      break;
    default:
      break; 
  }
  
  
}
