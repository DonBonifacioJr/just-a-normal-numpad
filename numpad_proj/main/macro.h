#include "menu.h"
#include "NewKeys.h"
//#include "bitmaps.h"


void macro(MenuState& currState, int& subSelect, Adafruit_SSD1306& display);
void macroIconLoop (int subSelect, Adafruit_SSD1306& display);
void macroOutputLoop (int subSelect, Adafruit_SSD1306& display);

//void macroChange(int& subSelect, Adafruit_SSD1306& display);

void musicMacros(int num, Adafruit_SSD1306& display);
void artMacros(int num, Adafruit_SSD1306& display);
void genMacros(int num, Adafruit_SSD1306& display);
