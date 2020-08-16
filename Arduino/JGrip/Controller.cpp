#include "Arduino.h"
#include "Controller.h"

Controller::Controller(Button buttons[], int numButtons) {
  this->buttons = buttons;
  this->numButtons = numButtons;
}

int Controller::getHeldButtons() {
  int state = 0;
  for(int i = 0; i < numButtons; i++) {
    if(buttons[i].isHeld()) {
      state |= (1 << i);
    }
  }
  return state;
}

void Controller::proceed() {
  for(int i = 0; i < numButtons; i++) {
    buttons[i].checkState();
    
//    if(buttons[i].pin == 7) {
//      buttons[i].log();
//    }
  }
}



