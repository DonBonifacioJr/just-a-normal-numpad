#include "HID-Project.h"
#include <Encoder.h>


Encoder myEnc(1, 0);

int backButtonPin = 8;
int playButtonPin = 7;
int skipButtonPin = 6;
int muteButtonPin = 5;

int debounceDelay = 150;

long unsigned lastMutePress;
long unsigned lastBackPress;
long unsigned lastPlayPress;
long unsigned lastSkipPress;

long oldPosition  = -999;
long newPosition;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  for(int i = 5; i < 9; i++) {
    pinMode(i, INPUT_PULLUP);
  }
//  pinMode(backButtonPin, INPUT_PULLUP);
//  pinMode(playButtonPin, INPUT_PULLUP);
//  pinMode(skipButtonPin, INPUT_PULLUP);
//  pinMode(muteButtonPin, INPUT_PULLUP);
  

}

void loop() {
  
  // put your main code here, to run repeatedly:
  encoderControl();
  backButton();
  playButton();
  skipButton();
  muteButton();

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

void backButton() {
  int buttonState = digitalRead(backButtonPin);
  long unsigned curr_time = millis();
  if ((curr_time - lastBackPress) > debounceDelay) //if the time between the last buttonChange is greater than the debounceTime
  {
    if (buttonState == LOW) //if button is pressed and was released last change
    {
      Consumer.write(MEDIA_PREVIOUS);
      lastBackPress = curr_time;
      //Serial.println("Previous");
      
    }
  }
}

void playButton() {
  int buttonState = digitalRead(playButtonPin);
  long unsigned curr_time = millis();
  if ((curr_time - lastPlayPress) > debounceDelay) //if the time between the last buttonChange is greater than the debounceTime
  {
    if (buttonState == LOW) //if button is pressed and was released last change
    {
      Consumer.write(MEDIA_PLAY_PAUSE);
      lastPlayPress = curr_time;
      //Serial.println("Play/Paused");
    }
  }
}

void skipButton() {
  int buttonState = digitalRead(skipButtonPin);
  long unsigned curr_time = millis();
  if ((curr_time - lastSkipPress) > debounceDelay) //if the time between the last buttonChange is greater than the debounceTime
  {
    if (buttonState == LOW) //if button is pressed and was released last change
    {
      Consumer.write(MEDIA_NEXT);
      lastSkipPress = curr_time;
      //Serial.println("Skipped");
    }
  }
}

void muteButton() {
  int buttonState = digitalRead(muteButtonPin);
  long unsigned curr_time = millis();
  if ((curr_time - lastMutePress) > debounceDelay) //if the time between the last buttonChange is greater than the debounceTime
  {
    if (buttonState == LOW) //if button is pressed and was released last 
    {
      Consumer.write(MEDIA_VOLUME_MUTE);
      lastMutePress = curr_time;
      //Serial.println("Muted");
    }
  }
}
