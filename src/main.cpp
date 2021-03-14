#include "fcore/main.h"

#include <Arduino.h>

button btn;
rgbled rgb;
felixmeter* fm;

void setup() {
    init_framework();

    fm = new felixmeter(1);

    fm->reaccurate();
    fm->run(8, 255, 255, 100);
}

void loop() {
}