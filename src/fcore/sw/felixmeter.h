#ifndef FELIXMETER_H_
#define FELIXMETER_H_

#include "../hw/config.h"
#include "../hw/linefollower.h"
#include "../hw/motor.h"
#include "../hw/port.h"
#include "PID.h"

class felixmeter : private linefollower, private motor {
   public:
    felixmeter(int port_num, bool side);
    void reaccurate();
    void run(int sector, int16_t m1, int16_t m2, int16_t brake_speed);
    void bindPID(PID *pid);

   private:
    PID *pid_control;
    bool availablePID;
    bool side;
    int felixmeterReadSensor();
};

#endif