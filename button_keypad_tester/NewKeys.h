
#include "HID-Project.h"

class NewKeys {
  private:
    int trueCols;
    int trueRows;
    char keys[3][3] = {                //correspondence with the keys of the keypad
      {'1', '2', '3'},
      {'4', '5', '6'},
      {'7', '8', '9'}
    };
    char lastKey = '0';

int pinCols[3]={7,8,9};
int pinRows[3]={6,5,4};
    
  public:
    void single_key_switcher(int i) {
      char keys_1 [3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
      };
      char keys_2 [3][3] = {
        {'a', 'b', 'c'},
        {'d', 'e', 'f'},
        {'g', 'h', 'i'}
      };
      char keys_3 [3][3] = {
        {'1', 'k', '3'},
        {'4', 'j', 'f'},
        {'7', '8', 'd'}
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
      for (int c = 0; c < 3; c++) {
        digitalWrite(pinCols[c], HIGH);
        //Serial.println(pinCols[c]);
        for (int r = 0; r < 3; r++) {
          if (digitalRead(pinRows[r]) == HIGH) {
            Keyboard.press(keys[r][c]);
            Serial.println("Current Key: ");
            Serial.println(keys[r][c]);
            lastKey = keys[r][c];
          }
          else {
            Keyboard.release(keys[r][c]);
          }
        }
        digitalWrite(pinCols[c], LOW);
      }
      //delay(1);
    }

    char getLastKey() {
      return lastKey;
    }
    

};
