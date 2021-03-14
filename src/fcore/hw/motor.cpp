#include "motor.h"

motor::motor() {
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(7, OUTPUT);
}

void motor::run(int16_t m1, int16_t m2) {
    if (m1 > 0) {
        digitalWrite(7, LOW);
    } else {
        digitalWrite(7, HIGH);
    }
    if (m2 < 0) {
        digitalWrite(4, LOW);
    } else {
        digitalWrite(4, HIGH);
    }
    analogWrite(6, abs(m1));
    analogWrite(5, abs(m2));
}

void motor::smooth_run(int16_t m1, int16_t m2) {
    run(255, 255);
    delay(10);
    run(m1, m2);
}