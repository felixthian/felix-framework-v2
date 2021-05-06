#include "felixmeter.h"

int felixmeter::felixmeterReadSensor() {
    if (side == s1) {
        return linefollower::readSensor1();
    } else {
        return linefollower::readSensor2();
    }
    return 9487;
}

felixmeter::felixmeter(int port_num, bool side) : linefollower(port_num), motor() {
    availablePID = false;
}

void felixmeter::reaccurate() {
    motor::run(120, 120);
}

int swap(int state) {
    if (state == HIGH) {
        return LOW;
    }
    if (state == LOW) {
        return HIGH;
    }
    return 9487;
}

void felixmeter::run(int sector, int16_t m1, int16_t m2, int16_t brake_speed) {
    if (!availablePID) {
        int travelledStep = 0;
        int nextStepState = swap(felixmeterReadSensor());
        bool isMotorReverse = false;
        motor::run(m1, m2);
        float lasttime = millis();
        double fix = 0;
        bool isDone = false;
        int repeatTarget = 0;
        while (!isDone) {
            if (felixmeterReadSensor() == nextStepState) {
                nextStepState = swap(nextStepState);
                if (isMotorReverse) {
                    travelledStep--;
                } else {
                    travelledStep++;
                }
            }

            if (travelledStep > sector) {
                fix = -1;
            } else if (travelledStep == sector) {
                fix = 0;
            } else {
                fix = 1;
            }
            motor::run((int16_t)(double)m1 * constrain(fix, -1.0, 1.0), (int16_t)(double)m2 * constrain(fix, -1.0, 1.0));
            if (fix < 0) {
                isMotorReverse = true;
            } else {
                isMotorReverse = false;
            }

            if ((millis() - lasttime) > 100) {
                lasttime = millis();
                //Serial.print("travelled step: ");
                Serial.println(travelledStep, DEC);
                //Serial.print("fix: ");
                //Serial.print(fix, DEC);
                //Serial.print("\n");
                if (travelledStep == sector) {
                    repeatTarget++;
                    if (repeatTarget >= 3) {
                        isDone = true;
                    }
                } else {
                    repeatTarget = 0;
                }
            }
        }
        motor::run(0, 0);
    } else {
        int travelledStep = 0;
        int nextStepState = swap(felixmeterReadSensor());
        bool isMotorReverse = false;
        motor::run(m1, m2);
        float lasttime = millis();
        Serial.println(sector, DEC);
        pid_control->readyPID();
        bool isDone = false;
        int repeatTarget = 0;
        while (!isDone) {
            if (felixmeterReadSensor() == nextStepState) {
                nextStepState = swap(nextStepState);
                if (isMotorReverse) {
                    travelledStep--;
                } else {
                    travelledStep++;
                }
            }

            if ((millis() - lasttime) > 100) {
                double fix = pid_control->computePID((double)sector, travelledStep);
                motor::run((int16_t)(double)m1 * constrain(fix, -1.0, 1.0), (int16_t)(double)m2 * constrain(fix, -1.0, 1.0));
                if (fix < 0) {
                    isMotorReverse = true;
                } else {
                    isMotorReverse = false;
                }
                lasttime = millis();
                //Serial.print("travelled step: ");
                Serial.println(travelledStep, DEC);
                //Serial.print("fix: ");
                //Serial.print(fix, DEC);
                //Serial.print("\n");
                if (travelledStep == sector) {
                    repeatTarget++;
                    if (repeatTarget >= 3) {
                        isDone = true;
                    }
                } else {
                    repeatTarget = 0;
                }
            }
        }
        motor::run(0, 0);
    }
}

void felixmeter::bindPID(PID *pid) {
    pid_control = pid;
    availablePID = true;
}