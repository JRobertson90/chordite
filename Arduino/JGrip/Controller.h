#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Button.h"

class Controller {

  public:
    Controller(Button buttons[], int numButtons);
    
    // Methods
    void proceed();
    int getHeldButtons();

    // Fields
    Button* buttons;
    int numButtons;
};

#endif
