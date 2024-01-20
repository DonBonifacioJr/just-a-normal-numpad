#ifndef NEWKEYS_H
#define NEWKEYS_H
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
    int currKeyboard = 0;

int pinCols[3]={7,8,9};
int pinRows[3]={6,5,4};
    
  public:
    // currKeyboard must be set prior to calling the function to change keyboard
    void single_key_switcher() {
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
        {'q', 'w', 'e'},
        {'a', 's', 'd'},
        {'z', 'x', ' '}
      };
      char keys_4 [3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
      };
      switch (currKeyboard) {
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
        case 3:
          for (int c = 0; c < 3; c++) {
            for (int r = 0; r < 3; r++) {
              keys[r][c] = keys_4[r][c];
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

    // Read key inputs.
    void readKey() {
      // When high is read on the row where column is set to high, the button is considered pressed
      for (int c = 0; c < 3; c++) {
        // Sets current column to high
        digitalWrite(pinCols[c], HIGH);
        //Serial.println(pinCols[c]);
        for (int r = 0; r < 3; r++) {
          if (digitalRead(pinRows[r]) == HIGH) {
            Keyboard.press(keys[r][c]);
            // Print current key being pressed
            Serial.println("Current Key: ");
            Serial.println(keys[r][c]);
            
            lastKey = keys[r][c];
          }
          else {
            Keyboard.release(keys[r][c]);
          }
        }
        // Set the column back to low
        digitalWrite(pinCols[c], LOW);
      }
      //delay(1);
    }

    char readInput() {
      int sum = 0;
      currKeyboard = 0;
      single_key_switcher();
      for (int c = 0; c < 3; c++) {
        // Sets current column to high
        digitalWrite(pinCols[c], HIGH);
        for (int r = 0; r < 3; r++) {
          if (digitalRead(pinRows[r]) == HIGH) {
            
            sum += keys[r][c];
            
          }
        }
        // Set the column back to low
        digitalWrite(pinCols[c], LOW);
      }

      //Serial.println(sum);
      return sum;
    }

    char getLastKey() {
      return lastKey;
    }

    void setKeyboard(int val) {
      currKeyboard = val;
    }

    int getKeyboard() const{
      return currKeyboard;
    }

};

//NewKeys key;

#endif
