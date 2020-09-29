#ifndef SERIAL_H_
#define SERIAL_H_

#include <Arduino.h>
#include <string.h>

class serial {
   public:
    serial(uint64_t baudrate);
    void log(String msg);
    void log_no_newline(String msg);
    void write(int msg);
};

#endif