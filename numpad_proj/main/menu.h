#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
#include "MenuState.h"
#include "bitmaps.h"



void Menu (MenuState& currState, MenuState& lastState, int& subSelect, Adafruit_SSD1306& display);
