/**
 * This is an experimental keyboard replacement 
 * using a pair of joysticks that I made myself
 * and a couple of SparkFun Pro Micro microcontrollers.
 * 
 * Copyright 2016 Jason Robertson
 */
#include "Arduino.h"
#include "Controller.h"
#include "Keyboard.h"
#include "Mappings.cpp"
#include <SoftwareSerial.h>

#define RX 10
#define TX 16
#define INITIAL_DELAY 500
#define REPEAT_DELAY 83
#define INITIAL_DELAY_FAST 100
#define REPEAT_DELAY_FAST 20

//SoftwareSerial mySerial(RX, TX);

// thumb, index, middle, ring, pinky
const static int NUM_BUTTONS = 5;
Button leftButtons[] = {2,3,4,5,6};
Button rightButtons[] = {7,8,9,14,15};

Controller left(leftButtons, NUM_BUTTONS);
Controller right(rightButtons, NUM_BUTTONS);

unsigned long prevRepeatTime = 0;

void setup() {
  Serial.begin(115200);
//  pinMode(RX, INPUT);
//  pinMode(TX, OUTPUT);
//  mySerial.begin(9600);
}

void loop() {
  left.proceed();
  right.proceed();
  process();
  delay(1);
}

/** 
 *  If a right button was pressed, then send to keyboard
 *  depending on which buttons were held in left hand. 
 */
void process() {
  for(int i = 0; i < right.numButtons; i++) {
    if(right.buttons[i].isPressed() || right.buttons[i].isHeld()) {
      int leftButtonsHeld = left.getHeldButtons();
      
      // Press a key.
      if(right.buttons[i].isPressed()) {
        Keyboard.write(mappings[leftButtonsHeld][i]);
      }

      // Repeat a key if held.
      if(right.buttons[i].isHeld() && right.buttons[i].timeHeld() > (isArrowKey(leftButtonsHeld, i) ? INITIAL_DELAY_FAST : INITIAL_DELAY)) {
        if((millis() - prevRepeatTime) > (isArrowKey(leftButtonsHeld, i) ? REPEAT_DELAY_FAST : REPEAT_DELAY)) {
          prevRepeatTime = millis();
          Keyboard.write(mappings[left.getHeldButtons()][i]);
        }
      }
    }
  }
}

boolean isArrowKey(int leftButtonsHeld, int rightButtonIndexPressed) {
  return leftButtonsHeld == 0 && rightButtonIndexPressed != 0;
}

