#ifndef LINE_FOLLOW_ALGO_H_
#define LINE_FOLLOE_ALGO_H_

#include <Arduino.h>

typedef bool (*leftSensorFunc)(void);
typedef bool (*rightSensorFunc)(void);

#define lf_speed 150
#define slow_side_factor 3

class LineFollowerAlgo {
   private:
    int m1val;
    int m2val;
    bool prev_side_right;

   public:
    LineFollowerAlgo();
    void calculate(bool leftState, bool rightState);
    int get_m1();
    int get_m2();
};

#endif