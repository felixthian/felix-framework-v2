#include "felixmeter.h"

int felixmeter::felixmeterReadSensor() {
    if (side == s1) {
        //Serial.println(F("s1 read"));
        return linefollower::readSensor1();
    } else {
        //Serial.println(F("s2 read"));
        return linefollower::readSensor2();
    }
    //Serial.println(F("s3 read"));
    return 9487;
}

felixmeter::felixmeter(int port_num, bool side_sensor) : linefollower(port_num), motor() {
    side = side_sensor;
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

void felixmeter::run(int sector, int16_t m1, int16_t m2, float brake_speed) {
    if (!availablePID) {
        int travelledStep = 0;
        int nextStepState = swap(felixmeterReadSensor());
        bool isMotorReverse = false;
        motor::run(m1, m2);
        float lasttime = millis();
        double fix = 0;
        bool isDone = false;
        int repeatTarget = 0;
        int slowingStep = sector / 2;
        while (!isDone) {
            if (felixmeterReadSensor() == nextStepState) {
                nextStepState = swap(nextStepState);
                if (isMotorReverse) {
                    travelledStep--;
                } else {
                    travelledStep++;
                    //travelledStep--;
                }
            }

            if (travelledStep > sector) {
                fix = -1;
            } else if (travelledStep == sector) {
                fix = 0;
            } else {
                fix = 1;
            }
            if (abs(travelledStep - sector) > slowingStep) {
                motor::run((int16_t)(double)m1 * constrain(fix, -1.0, 1.0), (int16_t)(double)m2 * constrain(fix, -1.0, 1.0));
            } else {
                motor::run((int16_t)(double)m1 * brake_speed * constrain(fix, -1.0, 1.0), (int16_t)(double)m2 * brake_speed * constrain(fix, -1.0, 1.0));
            }
            if (fix < 0) {
                isMotorReverse = true;
            } else {
                isMotorReverse = false;
            }

            if ((millis() - lasttime) > 100) {
                lasttime = millis();
                Serial.println(travelledStep, DEC);
                if (travelledStep == sector) {
                    repeatTarget++;
                    if (repeatTarget >= 5) {
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