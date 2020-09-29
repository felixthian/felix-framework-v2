#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#include <Arduino.h>
#include <stdint.h>

class light_sensor {
   public:
    light_sensor();
    int read();
};

#endif