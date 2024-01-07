#include "menu.h"
#include "keypad.h"]
#include "MenuState.h"


void Menu (MenuState& currState, Adafruit_SSD1306& display) {
  
  switch(currState) {
    case KEYPAD:
      keypad(currState, display);
      break;
    case MENUOPEN:
      //menuScreen();
      //currState = GetNextState();
      break;
    case ACTIVITY:
      break;
    case MACRO:
      break;
    case ERR:
      break;
    default:
      break; 
  }
  
  
}

//Menustate GetNextState() {
  
//}
