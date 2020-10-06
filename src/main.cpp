#include "fcore/main.h"

#include <Arduino.h>

button btn;
rgbled rgb;

void setup() {
    init_framework();
}

void loop() {
    if (btn.is_pressed()) {
        rgb.setColor(255, 0, 0);
    } else {
        rgb.setColor(0, 255, 0);
    }
}