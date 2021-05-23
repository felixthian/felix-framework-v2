#include "button.h"

button::button() { pinMode(A7, INPUT); }

bool button::is_pressed() {
    if (analogRead(A7) > 100) {
        return false;
    } else {
        return true;
    }
}

void button::waitForPress() {
    while (!is_pressed()) {}
    while (is_pressed()) {}
}