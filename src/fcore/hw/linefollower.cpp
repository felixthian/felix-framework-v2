#include "linefollower.h"

linefollower::linefollower(int port_num) : port(port_num - 1) {}

uint8_t linefollower::readSensor() {
    uint8_t state = S1_B_S2_B;
    bool s1State = port::dread(s1);
    bool s2State = port::dread(s2);
    state = ((1 & s1State) << 1) | s2State;
    return (state);
}

int linefollower::readSensor1() {
    return port::dread(s1);
}

int linefollower::readSensor2() {
    return port::dread(s2);
}