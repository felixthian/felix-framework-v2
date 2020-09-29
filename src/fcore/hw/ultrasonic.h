#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "port.h"

class ultrasonic : public port {
   public:
    ultrasonic(int port_num);
    double distanceCm();
   private:
    volatile uint8_t _SignalPin;
    volatile bool _measureFlag;
    volatile long _lastEnterTime;
    volatile float _measureValue;
    long measure();
};

#endif