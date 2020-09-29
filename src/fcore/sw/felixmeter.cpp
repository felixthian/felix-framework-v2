#include "felixmeter.h"

felixmeter::felixmeter(int port_num) : linefollower(port_num), motor() {}

void felixmeter::reaccurate() {
    motor::run(120, 120);
    int now = linefollower::readSensor2();
    int target = swap(now);
    while (now != target) {
        now = linefollower::readSensor2();
    }
    motor::run(0, 0);
}

int felixmeter::swap(int state) {
    if (state == HIGH) {
        return LOW;
    } else if (state == LOW) {
        return HIGH;
    }
    return 9487;
}

void felixmeter::run(int sector, int16_t m1, int16_t m2) {
    int now = linefollower::readSensor2();
    int target = swap(now);
    motor::run(m1, m2);
    for (int i = 0; i < sector; i++) {
        while (target != now) {
            now = linefollower::readSensor2();
        }
        target = swap(target);
        while (target != now) {
            now = linefollower::readSensor2();
        }
        // motor::run(0, 0);
        target = swap(target);
        // delay(200);
    }
    motor::run(0, 0);
}