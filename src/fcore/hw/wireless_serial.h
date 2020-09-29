#ifndef WIRELESS_SERIAL_H_
#define WIRELESS_SERIAL_H_

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../hw/port.h"

class fserial : protected SoftwareSerial {
   public:
    fserial(int port_num);
    void write(String msg);
    int Read();
    int available();

   protected:
    SoftwareSerial *ss;
};

#endif