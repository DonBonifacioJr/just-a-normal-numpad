#include "menu.h"
//#include "bitmaps.h"

void menuScreen (MenuState& currState, MenuState& lastState, int& subSelect, Adafruit_SSD1306& display);

void DisplayMenuLoopLabels(Adafruit_SSD1306& display);
void DisplayCursorLoop(Adafruit_SSD1306& display);

void MenuNavigator();
void optionSelector (MenuState& currState, MenuState lastState, int& subSelect, Adafruit_SSD1306& display);
