#ifndef CONFIG_H_
#define CONFIG_H_

#define DEBUG

#include <Arduino.h>

#include "../sw/serial.h"
#include "buzzer.h"

#ifdef DEBUG
extern buzzer debuz;
extern serial *debug;
#endif

void init_framework();

#endif