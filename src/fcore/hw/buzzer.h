#ifndef BUZZER_H_
#define BUZZER_H_

#include <stdint.h>
#include <Arduino.h>

class buzzer {
   public:
    buzzer();
    void tone(uint16_t frequency, uint32_t duration);
};

#endif