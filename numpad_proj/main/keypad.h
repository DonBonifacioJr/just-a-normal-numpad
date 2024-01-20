#include <Wire.h>
#include <SPI.h>
#include "menu.h"
#include "NewKeys.h"


// Main keypad loop
void keypad(MenuState& currState, Adafruit_SSD1306& display);

// Display functions
void DisplayKeysLoop(Adafruit_SSD1306& display);
void printKeysFormat(Adafruit_SSD1306& display);
void printKeysMessage(Adafruit_SSD1306& display);

// Change current keypad
void keypadChange(NewKeys& keys, Adafruit_SSD1306& display);
