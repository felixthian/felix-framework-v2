#include "buzzer.h"

buzzer::buzzer() { pinMode(8, OUTPUT); }
void buzzer::tone(uint16_t frequency, uint32_t duration) {
    int period = 1000000L / frequency;
    int pulse = period / 2;
    pinMode(8, OUTPUT);
    for (uint32_t i = 0; i < duration * 1000L; i += period) {
        digitalWrite(8, HIGH);
        delayMicroseconds(pulse);
        digitalWrite(8, LOW);
        delayMicroseconds(pulse);
    }
}