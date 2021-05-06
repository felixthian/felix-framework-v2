#include "voltmeter.h"

Voltmeter::Voltmeter(int port_num, bool side) : port(port_num - 1) {
    meterSide = side;
}

float Voltmeter::readVolt() {
    return (port::aread(meterSide) * (5.0 / 1023.0));
}