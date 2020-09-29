#include "lightsensor.h"

light_sensor::light_sensor() { pinMode(A6, INPUT); }

int light_sensor::read() { return analogRead(A6); }