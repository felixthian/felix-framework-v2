#ifndef BUTTON_H_
#define BUTTON_H_

#include <Arduino.h>

class button {
   public:
    button();
    bool is_pressed();
    void waitForPress();
};

#endif