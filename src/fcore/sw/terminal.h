#ifndef TERMINAL_H_
#define TERMINAL_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../hw/wireless_serial.h"
#include "../hw/rgbled.h"
#include "../hw/buzzer.h"
#include "felixmeter.h"

class terminal : private fserial, rgbled, buzzer, felixmeter {
    public:
    terminal(int port_num, int felixmeter_port);
};

#endif