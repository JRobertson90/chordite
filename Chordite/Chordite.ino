/**
 * This is an experimental keyboard replacement 
 * using a pair of joysticks that I made myself
 * and a couple of SparkFun Pro Micro microcontrollers.
 * 
 * Copyright 2016 Jason Robertson
 */
#include "Arduino.h"
#include "Keyboard.h"
#include "Button.h"
//#include <SoftwareSerial.h>

#define RX 10
#define TX 16
#define INITIAL_DELAY 500
#define REPEAT_DELAY 83
#define INITIAL_DELAY_FAST 100
#define REPEAT_DELAY_FAST 20

const static int L_NUM_BUTTONS = 8;
const static int R_NUM_BUTTONS = 4;
Button l_buttons[] = {5,4,3,2,9,8,7,6};
Button r_buttons[] = {15,14,16,18};
int sequence = 1;
int first_button_pressed = -1;
const static char combo_mappings[8][4] = {
/* 0  */ {'a','b','c','d'}, // 1
/* 1  */ {'e','f','g','h'}, // 2
/* 2  */ {'i','j','k','l'}, // 3
/* 3  */ {'m','n','o','p'}, // 4
/* 4  */ {'q','r','s','t'}, // 1'
/* 5  */ {'u','v','w','x'}, // 2'
/* 6  */ {'y','z','1','2'}, // 3'
/* 7  */ {'3','4','5','6'}  // 4'
};
const static char r_mappings[4] = {(char)216,(char)217,(char)218,(char)215};

//SoftwareSerial mySerial(RX, TX);
//unsigned long prevRepeatTime = 0;
//Controller controller(buttons, NUM_BUTTONS);

void setup() {
//  Serial.begin(115200);
//  pinMode(RX, INPUT);
//  pinMode(TX, OUTPUT);
//  mySerial.begin(9600);
}

void loop() {
  for(int i = 0; i < L_NUM_BUTTONS; i++) {
    l_buttons[i].checkState();
  }
  for(int i = 0; i < R_NUM_BUTTONS; i++) {
    r_buttons[i].checkState();
  }
  process();
  delay(1);
}

void process() {
  int l = nextLeftButton();
  int r = nextRightButton();
  if(l != -1 || r != -1) {
    if(sequence == 1) {
      if(l != -1) {
        first_button_pressed = l;
        nextSequence();
      } else if (r != -1) {
        Keyboard.write(r_mappings[r]);
      }
    } else if (sequence == 2 && r != -1) {    
      Keyboard.write(combo_mappings[first_button_pressed][r]);
      nextSequence();
    }
  }    
}

int nextLeftButton() {
  for(int i = 0; i < L_NUM_BUTTONS; i++) {
    if(l_buttons[i].isPressed()) {
      return i;
    }
  }
  return -1;
}

int nextRightButton() {
  for(int i = 0; i < R_NUM_BUTTONS; i++) {
    if(r_buttons[i].isPressed()) {
      return i;
    }
  }
  return -1;
}

void nextSequence() {
  sequence++;
  if(sequence > 2) {
    sequence = 1;
  }
}
  
      // Repeat a key if held.
//      if(right.buttons[i].isHeld() && right.buttons[i].timeHeld() > (isArrowKey(leftButtonsHeld, i) ? INITIAL_DELAY_FAST : INITIAL_DELAY)) {
//        if((millis() - prevRepeatTime) > (isArrowKey(leftButtonsHeld, i) ? REPEAT_DELAY_FAST : REPEAT_DELAY)) {
//          prevRepeatTime = millis();
//          Keyboard.write(mappings[left.getHeldButtons()][i]);
//        }
//      }

//boolean isArrowKey(int leftButtonsHeld, int rightButtonIndexPressed) {
//  return leftButtonsHeld == 0 && rightButtonIndexPressed != 0;
//}

