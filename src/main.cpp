#include "fcore/main.h"

#include <Arduino.h>

button btn;
rgbled rgb;
felixmeter* fm;
PID* pid;
Voltmeter* volt;
motor *m;

void setup() {
    init_framework();
    //Serial.begin(115200);

    delay(1000);

    //m = new motor();
    //m->run(255, 255);
    //volt = new Voltmeter(3, s1);

    //pid = new PID(0.1, 0.001, 0.005);
    fm = new felixmeter(2, s1);
    //fm->bindPID(pid);
    //fm->reaccurate();
    fm->run(15, 0, 200, 100);
    //fm->run(31, 0, 200, 100);
    //Serial.println("bruh");
}

void loop() {
    //delay(500);
    //Serial.println(String(volt->readVolt()));
}