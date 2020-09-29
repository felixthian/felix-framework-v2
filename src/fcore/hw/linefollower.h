#ifndef LINEFOLLOWER_H_
#define LINEFOLLOWER_H_

#define S1_B_S2_B (0x00)
#define S1_B_S2_W (0x01)
#define S1_W_S2_B (0x02)
#define S1_W_S2_W (0x03)

#include "port.h"

class linefollower : private port {
   public:
    linefollower(int port_num);
    uint8_t readSensor();
    int readSensor1();
    int readSensor2();
};

#endif