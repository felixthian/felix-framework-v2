#ifndef PID_H_
#define PID_H_

#include <Arduino.h>

class PID {
   private:
    double Kp;
    double Ki;
    double Kd;

    unsigned long currentTime, previousTime;
    double elapsedTime;
    double net_error;
    double lastError;
    double input, output, setPoint;
    double cumError, rateError;

   public:
    PID(double Kp_in, double Ki_in, double Kd_in);
    void readyPID();
    double computePID(double target, double current);
};

#endif