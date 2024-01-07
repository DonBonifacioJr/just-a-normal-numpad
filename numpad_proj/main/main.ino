#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HID-Project.h"
#include <Encoder.h>
#include "MenuState.h"
#include "menu.h"

Adafruit_SSD1306 display(128, 64, &Wire, -1);

MenuState currState = KEYPAD;
MenuState lastState = KEYPAD;
//enum MenuState{Keypad, MenuOpen, Activity};


const int pinCols[3] = {7, 8, 9}; //pins of the differents columns 10 11 12
const int pinRows[3] = {6, 5, 4}; //pins of the differents rows 9 8 7

int selectorButton = 16;

int debounceDelay = 150;

#include "LoadingBar.h"
LoadingBar loading;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  pinMode(selectorButton, INPUT_PULLUP);

  for (int i = 0; i < 3; i++) {       //defining the output and input pins
    pinMode(pinCols[i], OUTPUT);
    digitalWrite(pinCols[i], LOW);
    pinMode(pinRows[i], INPUT);
  }

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize display
   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
     Serial.println(F("SSD1306 allocation failed"));
     for (;;); // Don't proceed, loop forever
   }
  loading.renderLoad();
  loading.deletion();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

}

void loop() {
  MenuState priorState = currState;
  Menu(currState, display);
  if (priorState != currState) {
    lastState = priorState;
  }

}
