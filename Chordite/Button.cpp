#include "Arduino.h"
#include "Button.h"

Button::Button(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
}

/* Returns true one time when the button is pressed. */
boolean Button::isPressed() {
  return !wasDebounced() && isDebounced() && isDown();
}

/* Returns true one time when the button is released. */
boolean Button::isReleased() {
  return !wasDebounced() && isDebounced() && isUp();
}

/* Returns true the entire time the button is held down. */
boolean Button::isHeld() {
  return isDebounced() && isDown();
}

/* Returns true the entire time the button is in the open position. */
boolean Button::isOpen() {
  return isDebounced() && isUp();
}

unsigned long Button::timeHeld() {
  return isHeld() ? currentTime - pressedStartTime : pressedEndTime - pressedStartTime;
}

void Button::checkState() {
  previousState = currentState;
  currentState = digitalRead(pin);
  
  previousTime = currentTime;
  currentTime = millis();
  
  if(previousState != currentState) {
    stateBeginTime = currentTime;
  }
  if(isPressed()) {
    pressedStartTime = currentTime;
  } else if(isReleased()) {
    pressedEndTime = currentTime;
  }
}

void Button::log() {
  Serial.println("===============");
  Serial.print("     PIN "); Serial.println(pin);
  Serial.println("===============");
  Serial.print("previousState:"); Serial.println(previousState);
  Serial.print("currentState:"); Serial.println(currentState);
  Serial.print("previousTime:"); Serial.println(previousTime);
  Serial.print("currentTime:"); Serial.println(currentTime);
  Serial.print("stateBeginTime:"); Serial.println(stateBeginTime);
}

boolean Button::isUp() {
  return currentState == HIGH;
}

boolean Button::isDown() {
  return currentState == LOW;
}

boolean Button::wasUp() {
  return previousState == HIGH;
}

boolean Button::wasDown() {
  return previousState == LOW;
}

boolean Button::isDebounced() {
  return (currentTime - stateBeginTime) > debounceDelay;
}

boolean Button::wasDebounced() {
  return (previousTime - stateBeginTime) > debounceDelay;
}

