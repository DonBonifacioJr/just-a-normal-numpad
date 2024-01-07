#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
#include "MenuState.h"



void Menu (MenuState& currState, Adafruit_SSD1306& display);

MenuState GetNextState(MenuState& currState);
