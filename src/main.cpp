#include "fcore/main.h"

#include <Arduino.h>

button btn;
rgbled* rgb;

void setup() {
    init_framework();
    delay(1000);
    rgb = new rgbled();
    rgb->setColor(0, 0, 255);
    delay(1000);
    btn.waitForPress();
    terminal term(2, 1);
}

void loop() {
}