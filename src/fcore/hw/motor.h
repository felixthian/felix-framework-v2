#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

class motor {
   public:
    motor();
    void run(int16_t m1, int16_t m2);
};

#endif