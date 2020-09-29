#ifndef FELIXMETER_H_
#define FELIXMETER_H_

#include "../hw/linefollower.h"
#include "../hw/motor.h"
#include "../hw/port.h"

class felixmeter : private linefollower, private motor {
   public:
    felixmeter(int port_num);
    void reaccurate();
    void run(int sector, int16_t m1, int16_t m2);

   private:
    int swap(int state);
};

#endif