#ifndef VOLTMETER_H_
#define VOLTMETER_H_

#include <Arduino.h>

#include "../hw/port.h"

class Voltmeter : private port {
   private:
    bool meterSide;

   public:
    Voltmeter(int port_num, bool side);
    float readVolt();
};

#endif