#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "HID-Project.h"
#include <Encoder.h>
#include "NewKeys.h"

// Keyboard Variables
NewKeys key;
int currKeyboard = 0;

const int pinCols[3] = {7, 8, 9}; //pins of the differents columns 10 11 12
const int pinRows[3] = {6, 5, 4}; //pins of the differents rows 9 8 7

// Encoder Set-up Variables
Encoder myEnc(0, 1);
int encoderButton = 10;
int encoderState;
int lastEncoderState = 1;
long unsigned lastEncoderPress;

// Variables for the current Keyboard Select Button
int selectorButton = 16;
int lastMenuButtonState = 0;
long unsigned pressStart = 0;

// Bubble Over Effect initial vars
long unsigned lastBubbleTime = 0;
int bubbleMode = 0;


int buttonPin = 6;
int debounceDelay = 150;

int menuState = 0;
int lastMenuState;

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#include "BubbleOver.h"
#include "LoadingBar.h"

LoadingBar loading;
BubbleOver bubbles;

long oldPosition  = -999;
long newPosition;

char oldKey = '0';


void setup() {
  Serial.begin(9600);
  
  //Encoder Switch
  pinMode(encoderButton, INPUT_PULLUP);
  //Menu Selector Switch
  pinMode(selectorButton, INPUT_PULLUP);

  for (int i = 0; i < 3; i++) {       //defining the output and input pins
    pinMode(pinCols[i], OUTPUT);
    digitalWrite(pinCols[i], LOW);
    pinMode(pinRows[i], INPUT);
  }
  //Consumer.begin();
  //loading.setup();

   display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize display
   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
     Serial.println(F("SSD1306 allocation failed"));
     for (;;); // Don't proceed, loop forever
   }
  loading.renderLoad();
  loading.deletion();
  //bubbles.setup();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
//  newPosition = myEnc.read();
//  //long newPositionChanged = newPosition / 2;
//  //newPosition = newPositionChanged;
//  if ((newPosition ) != (oldPosition )) {
//    if (newPosition > oldPosition) {
//      Consumer.write(MEDIA_VOLUME_UP);
//      //Keyboard.write(']');
//      oldPosition = newPosition;
//    }
//    else if (newPosition < oldPosition ) {
//      Consumer.write(MEDIA_VOLUME_DOWN);
//      //Keyboard.write('[');
//      oldPosition = newPosition;
//      //Serial.println(newPosition);
//    }
//    //Serial.println(newPosition);
//  }

  // Encoder Function
  encoderControl();
  encoderFunctionButton();

  // Menu Button
  menuSelectorButton(currKeyboard, lastMenuButtonState, pressStart, bubbles);

  
  key.single_key_switcher(currKeyboard);
  key.readKey();
  
  char lastKey = key.getLastKey();
  if (lastKey != oldKey) {
    bubbles.setFormatNum(0);
    bubbles.setMyMessage(String(lastKey));
    oldKey = lastKey;
  }
  
  bubbles.loop();
  
}


void encoderFunctionButton() {

  int buttonState = digitalRead(encoderButton);
  long unsigned curr_time = millis();
  if ((curr_time - lastEncoderPress) > debounceDelay) //if the time between the last buttonChange is greater than the debounceTime
  {
    if (buttonState == LOW) //if button is pressed and was released last change
    {
      Consumer.write(MEDIA_PLAY_PAUSE);
      lastEncoderPress = curr_time;//update lastPress
    }
  }
}

void menuSelectorButton(int &currKeyboard, int &lastMenuButtonState, long unsigned &pressStart, BubbleOver &bubbles) {
  int buttonState = digitalRead(selectorButton);
  

  if (buttonState != lastMenuButtonState) {
    pressStart = millis();
  }
  
  if ((millis() - pressStart) >= 75) {
    if (buttonState == 0) {
      if ((millis() - pressStart) >= 1500) {
        // Long-press is detected and keyboard changes!
        Serial.println("Keyboard has been Changed!");
        bubbles.keyChangeMessage();
        if (currKeyboard == 2) {
          currKeyboard = 0;
        }
        else {
          currKeyboard += 1;
        }
        pressStart = millis();
      }
    }
    // The button has been released
  }

  lastMenuButtonState = buttonState;
}

void menuOpen(int &menuState, int buttonPin) {
  int buttonState = digitalRead(buttonPin);
  long unsigned curr_time = millis();
  lastMenuState = menuState;
  if ((curr_time - lastEncoderPress) > debounceDelay) //if the time between the last buttonChange is greater than the debounceTime
  {
    
    if (buttonState == 1) //if button is pressed and was released last change
    {
      
      menuState =! menuState;
    }
  }
}

void encoderControl() {
  newPosition = myEnc.read();
  if ((newPosition ) != (oldPosition )) {
    if (newPosition > oldPosition) {
      
      Consumer.write(MEDIA_VOLUME_UP);
      //Keyboard.write(']');
      oldPosition = newPosition;
    }
    else if (newPosition < oldPosition ) {
      Consumer.write(MEDIA_VOLUME_DOWN);
      //Keyboard.write('[');
      oldPosition = newPosition;
      //Serial.println(newPosition);
    }
    //Serial.println(newPosition);
  }
}
