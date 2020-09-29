#include "serial.h"

serial::serial(uint64_t baudrate) { Serial.begin(baudrate); }
void serial::log_no_newline(String msg) { Serial.print(msg); }

void serial::log(String msg) {
    Serial.print("[log] ");
    Serial.print(msg);
    Serial.println(" ");
}

void serial::write(int msg) {
    Serial.write(msg);
}