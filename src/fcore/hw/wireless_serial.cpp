#include "wireless_serial.h"

#include "config.h"

fserial::fserial(int port_num) : SoftwareSerial(port_sig[port_num - 1].s2, port_sig[port_num - 1].s1) {
    pinMode(port_sig[port_num - 1].s2, INPUT);
    pinMode(port_sig[port_num - 1].s1, OUTPUT);
    SoftwareSerial::begin(115200);
#ifdef DEBUG
    debug->log_no_newline(F("RX: "));
    debug->log_no_newline(String(port_sig[port_num - 1].s2));
    debug->log_no_newline(F(" TX: "));
    debug->log_no_newline(String(port_sig[port_num - 1].s1));
    debug->log_no_newline(F("\n"));
#endif
}

void fserial::write(String msg) {
    SoftwareSerial::write(msg.c_str());
}
int fserial::Read() {
    return SoftwareSerial::read();
}
int fserial::available() {
    return SoftwareSerial::available();
}