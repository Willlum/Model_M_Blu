#include <Arduino.h>
#include <BleKeyboard.h>
#include "keymap.h"
#include "PCF8575.h"

#define NUM_LOCK 4 
#define CAPS_LOCK 16
#define SCROLL_LOCK 17 

PCF8575 PCF(0x20);
BleKeyboard bleKeyboard;
int keyLayer;
int capState = 1;

void setup() {
 
  Serial.begin(115200);

  pinMode(SCROLL_LOCK, OUTPUT);
  pinMode(CAPS_LOCK, OUTPUT);
  pinMode(NUM_LOCK, OUTPUT);
    
  PCF.begin();
  if (!PCF.isConnected())
  {
    while(1){
      digitalWrite(NUM_LOCK,HIGH);
      delay(250);
      digitalWrite(NUM_LOCK,LOW);
      delay(250);
    }
  }

  digitalWrite(SCROLL_LOCK,LOW);
  digitalWrite(CAPS_LOCK,LOW);
  digitalWrite(NUM_LOCK,LOW);
  delay(500);
  digitalWrite(SCROLL_LOCK,HIGH);
  digitalWrite(CAPS_LOCK,HIGH);
  digitalWrite(NUM_LOCK,HIGH);
  delay(250);

  //Set all inputs to low on gpio expander
  PCF.write16(0x00);
  
  for (int i = 0; i < MATRIX_ROWS; i++)
  {
    pinMode(rows[i], INPUT_PULLDOWN);
  }
  keyLayer = 0;
  bleKeyboard.begin();
}

void loop(){
  if(!bleKeyboard.isConnected()) {
    digitalWrite(SCROLL_LOCK,LOW);
    delay(250);
    digitalWrite(CAPS_LOCK,LOW);
    delay(250);
    digitalWrite(NUM_LOCK,LOW);
    delay(250);
    digitalWrite(SCROLL_LOCK,HIGH);
    digitalWrite(CAPS_LOCK,HIGH);
    digitalWrite(NUM_LOCK,HIGH);
    delay(250);
  } 
  else{
    for (int colCnt = 0;colCnt < MATRIX_COLS; colCnt++){
      PCF.write(colCnt, HIGH);  
      for (int rowCnt = 0;rowCnt < MATRIX_ROWS; rowCnt++){
          
          int col = 15 - colCnt;

          //Key pressed for the first time
          if(digitalRead(rows[rowCnt]) && pressedMap[keyLayer][rowCnt][col] == false ){
            switch(keymap[keyLayer][rowCnt][col]){
              case KEY_CAPS_LOCK:
                capState = !digitalRead(CAPS_LOCK); //add debounce?
                digitalWrite(CAPS_LOCK, capState);
                pressedMap[keyLayer][rowCnt][col] = true;
                keyLayer = !capState; //inverted becasue of LED logic
                break;
              case KEY_LEFT_SHIFT:
                bleKeyboard.press(keymap[keyLayer][rowCnt][col]);
                pressedMap[keyLayer][rowCnt][col] = true;
                keyLayer = capState;
                break;
              case KEY_RIGHT_SHIFT:
                bleKeyboard.press(keymap[keyLayer][rowCnt][col]);
                pressedMap[keyLayer][rowCnt][col] = true;
                keyLayer = capState;
                break;
              default:
                bleKeyboard.press(keymap[keyLayer][rowCnt][col]);
                pressedMap[keyLayer][rowCnt][col] = true;
                Serial.print(keyLayer);
                Serial.print(",");
                Serial.print(rowCnt);
                Serial.print(",");
                Serial.print(col);
                Serial.print(",");
                Serial.println(keymap[keyLayer][rowCnt][col]);
            }
          }
        
          //Key released
          else if(!digitalRead(rows[rowCnt]) && pressedMap[keyLayer][rowCnt][col] == true){
            switch(keymap[keyLayer][rowCnt][col]){
              case KEY_LEFT_SHIFT:
                if(capState) keyLayer = 0; //inverted becasue of LED logic
                else keyLayer = !capState;
                bleKeyboard.release(keymap[keyLayer][rowCnt][col]);
                pressedMap[keyLayer][rowCnt][col] = false;
                break;
              case KEY_RIGHT_SHIFT:
                if(capState) keyLayer = 0;
                else keyLayer = !capState;
                bleKeyboard.release(keymap[keyLayer][rowCnt][col]);
                pressedMap[keyLayer][rowCnt][col] = false;
                break;
              default:
                bleKeyboard.release(keymap[keyLayer][rowCnt][col]);
                pressedMap[keyLayer][rowCnt][col] = false;
            } 
          }
      }
      PCF.write(colCnt, LOW);  
    }
    delay(1);          
  }
}