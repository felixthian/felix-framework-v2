#include "PID.h"

PID::PID(double Kp_in, double Ki_in, double Kd_in) {
    Kp = Kp_in;
    Ki = Ki_in;
    Kd = Kd_in;

    cumError = 0;
}

void PID::readyPID() {
    currentTime = millis();
    previousTime = millis();
}

double PID::computePID(double target, double current) {
    currentTime = millis();
    elapsedTime = (double)(currentTime - previousTime);

    net_error = target - current;
    //Serial.println(elapsedTime, DEC);
    cumError += net_error * elapsedTime;
    rateError = (net_error - lastError) / elapsedTime;

    //Serial.println(net_error, DEC);
    //Serial.println(cumError, DEC);
    //Serial.println(rateError, DEC);
    double out = Kp * net_error + Ki * cumError + Kd * rateError;

    lastError = net_error;
    previousTime = currentTime;

    return out;
}