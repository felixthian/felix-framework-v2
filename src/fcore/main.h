#ifndef MAIN_H_
#define MAIN_H_


//hardwawre layer
#include "hw/config.h"
#include "hw/wireless_serial.h"
#include "hw/port.h"
#include "hw/motor.h"
#include "hw/buzzer.h"
#include "hw/rgbled.h"
#include "hw/lightsensor.h"
#include "hw/button.h"
#include "hw/bt.h"
#include "hw/4dotLineFollower.h"
#include "hw/ultrasonic.h"
#include "hw/RGBmatrix.h"

//software layer
#include "sw/serial.h"
#include "sw/felixmeter.h"
#include "sw/voltmeter.h"
#include "sw/mode_selector.h"
#include "sw/line_following_algorithm.hpp"

#endif