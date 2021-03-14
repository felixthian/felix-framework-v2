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

void felixmeter::run(int sector, int16_t m1, int16_t m2, int16_t brake_speed) {
    int now = linefollower::readSensor2();
    int target = now;
    motor::smooth_run(m1, m2);
    for (int i = 0; i < sector; i++) {
        if (i > (sector / 2)) {
            motor::run(constrain(m1, -brake_speed, brake_speed), constrain(m2, -brake_speed, brake_speed));
        }
        while (target != now) {
            if (linefollower::readSensor2() == linefollower::readSensor1()) {
                now = linefollower::readSensor2();
            }
        }
        target = swap(target);
        while (target != now) {
            if (linefollower::readSensor2() == linefollower::readSensor1()) {
                now = linefollower::readSensor2();
            }
        }
        // motor::run(0, 0);
        target = swap(target);
        // delay(200);
    }
    motor::run(0, 0);
    delay(100);
    bool is_brake_need = true;
    while (is_brake_need) {
        #ifdef DEBUG
            debug->log_no_newline(F("brake called: "));
        #endif
        is_brake_need = false;
        int lock = linefollower::readSensor2();
        motor::run(0, 0);
        delay(100);
        while (lock != linefollower::readSensor2() || lock != linefollower::readSensor1()) {
            motor::run(-constrain(m1, -brake_speed, brake_speed), -constrain(m2, -brake_speed, brake_speed));
            is_brake_need = true;
        }
        motor::run(constrain(m1, -brake_speed, brake_speed), constrain(m2, -brake_speed, brake_speed));
        delay(10);
        motor::run(0, 0);
        #ifdef DEBUG
            if (is_brake_need) {
                debug->log(F("true"));
            } else {
                debug->log(F("false"));
            }
        #endif
        
    }
    motor::run(0, 0);
}