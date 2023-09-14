#include <Arduino.h>
#include <Keyboard.h>
//int trueCols;
//int trueRows;
//char lastKey1;
//char currKey1;
//char lastKey2;
//char currKey2;
//int keyHold1 = 0;
//int keyHold2 = 0;
//int keyRollover = 0;
//
//

class SingleKey {
  private:
    int trueCols;
    int trueRows;
    char lastKey1;
    char currKey1;
    char lastKey2;
    char currKey2;
    int keyHold1 = 0;
    int keyHold2 = 0;
    int keyRollover = 0;
    char keys[3][3] = {                //correspondence with the keys of the keypad
      {'1', '2', '2'},
      {'4', '5', '6'},
      {'7', '8', '9'}
    };
//    int pinCols[3] = {10, 11, 12}; //pins of the differents columns
//    int pinRows[3] = {9, 8, 7}; //pins of the differents rows
int pinCols[3]={7,8,9};     //pins of the differents columns 10 11 12
int pinRows[3]={6,5,4};
    
  public:
    void single_key_switcher(int i) {
      char keys_1 [3][3] = {                //correspondence with the keys of the keypad
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
      };
      char keys_2 [3][3] = {                //correspondence with the keys of the keypad
        {'a', 'b', 'c'},
        {'d', 'e', 'f'},
        {'g', 'h', 'i'}
      };
      char keys_3 [3][3] = {                //correspondence with the keys of the keypad
        {'1', '2', 'j'},
        {'4', '5', 'f'},
        {'7', '8', '9'}
      };
      switch (i) {
        case 0:
          for (int c = 0; c < 3; c++) {
            for (int r = 0; r < 3; r++) {
              keys[r][c] = keys_1[r][c];
            }
          }
          break;
        case 1:
          for (int c = 0; c < 3; c++) {
            for (int r = 0; r < 3; r++) {
              keys[r][c] = keys_2[r][c];
            }
          }
          break;
        case 2:
          for (int c = 0; c < 3; c++) {
            for (int r = 0; r < 3; r++) {
              keys[r][c] = keys_3[r][c];
            }
          }
          break;
        default:
          for (int c = 0; c < 3; c++) {
            for (int r = 0; r < 3; r++) {
              keys[r][c] = keys[r][c];
            }
          }
          break;
      }
    }

    void readKey() {
      
      keyHold1 = 0;
      keyHold2 = 0;
      for (int c = 0; c < 3; c++) {
        digitalWrite(pinCols[c], HIGH);
        //Serial.println(pinCols[c]);
        for (int r = 0; r < 3; r++) {
          if (digitalRead(pinRows[r]) == HIGH) {
            if (keyHold1 == 1) {
              if (keyHold2 == 0) {
                keyHold2 = 1;
              }
              currKey2 = keys[r][c];
            }
            else {
              currKey1 = keys[r][c];
              keyHold1 = 1;
            }
          }
        }
        digitalWrite(pinCols[c], LOW);
      }
      //
      //  if ((keyHold1 == 1) && (keyHold2 == 0)) {
      //    currKey2 = currKey1;
      //  }

      //  if ((keyHold1 == 0) && (keyHold2 == 1)) {
      //    keyHold2 = 0;
      //    keyHold1 = 1;
      //    currKey1 = currKey2;
      //  }

      if ((keyHold1 == 1) || (keyHold2 == 1)) {
        if (keyHold1 == 1) {
          if ((lastKey1 != currKey1) && (keyHold2 == 0)) {
            currKey2 = lastKey1;
          }
          Keyboard.press(currKey1);
          lastKey1 = currKey1;
        }
        else {
          Keyboard.release(currKey1);
          Keyboard.release(lastKey1);
        }
        if (keyHold2 == 1) {
          if (currKey1 != currKey2) {
            Serial.println("Rollover is Active!");
            lastKey2 = currKey2;
            //Serial.println(currKey2);
          }
          Keyboard.press(currKey2);
        }
        else {
          if (currKey1 != currKey2) {
            Keyboard.release(currKey2);
            if (lastKey1 != currKey1) {
              Keyboard.release(lastKey1);
            }
          }
        }
      }
      else {
        Keyboard.releaseAll();
      }

      //Current Key 
        Serial.print("Current Key 1: ");
        Serial.println(currKey1);
        Serial.print("Current Key 2: ");
        Serial.println(currKey2);
        Serial.print("Key 1 is: ");
        Serial.println(keyHold1);
        Serial.print("Key 2 is: ");
        Serial.println(keyHold2);
        Serial.println();
      delay(5);
    }
    
    char getCurrKey1() {
      return currKey1;
    }
    char getCurrKey2() {
      return currKey2;
    }
    int getKeyHold1() {
      return keyHold1;
    }
    int getKeyHold2() {
      return keyHold2;
    }

};
