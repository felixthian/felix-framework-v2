#include "port.h"
#include "config.h"

const port_t port_sig[4] = {{11, 12}, {9, 10}, {A2, A3}, {A0, A1}};

const bool s1 = true;
const bool s2 = false;

port::port(int num) { pin = port_sig[num]; }

void port::dwrite(bool pins, bool data) {
    if (pins == s1) {
        pinMode(pin.s1, OUTPUT);
        digitalWrite(pin.s1, data);
    } else if (pins == s2) {
        pinMode(pin.s2, OUTPUT);
        digitalWrite(pin.s2, data);
    }
}

int port::dread(bool pins) {
    if (pins == s1) {
        pinMode(pin.s1, INPUT);
        return digitalRead(pin.s1);
    } else if (pins == s2) {
        pinMode(pin.s2, INPUT);
        return digitalRead(pin.s2);
    }
    return 9487;
}
int port::dpread(bool pins) {
    if (pins == s1) {
        pinMode(pin.s1, INPUT_PULLUP);
        return digitalRead(pin.s1);
    } else if (pins == s2) {
        pinMode(pin.s2, INPUT_PULLUP);
        return digitalRead(pin.s2);
    }
    return 9487;
}
void port::awrite(bool pins, uint8_t data) {
    if (pins == s1) {
        pinMode(pin.s1, OUTPUT);
        analogWrite(pin.s1, data);
    } else if (pins == s2) {
        pinMode(pin.s2, OUTPUT);
        analogWrite(pin.s2, data);
    }
}

int port::aread(bool pins) {
    if (pins == s1) {
        pinMode(pin.s1, INPUT);
        return analogRead(pin.s1);
    } else if (pins == s2) {
        pinMode(pin.s2, INPUT);
        return analogRead(pin.s2);
    }
    return 9487;
}

port_t port::get_port() {
#ifdef DEBUG
    debug->log_no_newline(F("s1: "));
    debug->log_no_newline(String(pin.s1));
    debug->log_no_newline(F(" s2: "));
    debug->log_no_newline(String(pin.s2));
    debug->log_no_newline(F("\n"));
#endif
    return pin;
}