#include "ultrasonic.h"

#include "config.h"

ultrasonic::ultrasonic(int port_num) : port(port_num - 1) {
}

double ultrasonic::distanceCm() {
#ifdef DEBUG
    debug->log_no_newline(F("reading ultrasonic sensor value... pin info: "));
    port::get_port();
#endif
    long distance = measure();

    if ((((double)distance / 58.0) >= 400.0) || (distance == 0)) {
        return ((double)400.0);
    } else {
        return ((double)distance / 58.0);
    }
}

long ultrasonic::measure() {
    long duration;
    if (millis() - _lastEnterTime > 23) {
        _measureFlag = true;
    }

    if (_measureFlag == true) {
        _lastEnterTime = millis();
        _measureFlag = false;
        port::dwrite(s2, LOW);
        delayMicroseconds(2);
        port::dwrite(s2, HIGH);
        delayMicroseconds(10);
        port::dwrite(s2, LOW);
        pinMode(port::pin.s2, INPUT);
        duration = pulseIn(port::pin.s2, HIGH);
        _measureValue = duration;
    } else {
        duration = _measureValue;
    }
    return (duration);
}