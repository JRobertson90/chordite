#ifndef BUTTON_H
#define BUTTON_H

class Button {

  public:
    Button(int pin);
    boolean isPressed();
    boolean isReleased();
    boolean isHeld();
    boolean isOpen();
    unsigned long timeHeld();
    void checkState();
    void log();
    int pin;
    
  private:
    boolean isUp();
    boolean isDown();
    boolean wasUp();
    boolean wasDown();
    boolean isDebounced();
    boolean wasDebounced();
    
    // Fields
    const static int debounceDelay = 20;
    unsigned long stateBeginTime = millis();
    unsigned long pressedStartTime = 0;
    unsigned long pressedEndTime = 0;
    unsigned long currentTime = millis();
    unsigned long previousTime = millis();
    int currentState = HIGH;
    int previousState = HIGH;
};

#endif
