#include "config.h"

#ifdef DEBUG
buzzer debuz;
serial *debug;
#endif

void init_framework() {
#ifdef DEBUG
    debug = new serial(115200);
#endif
}