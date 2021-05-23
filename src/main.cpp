#include "fcore/main.h"

#include <Arduino.h>

felixmeter *fm;
MeLEDMatrix *rgbmat;
ModeSelector *mode;
ultrasonic *uls;
rgbled *led;
motor *m;
LineFollowerAlgo *lf_algo;
rgblinefollower *rgblf;
buzzer *buzz;

void modeDispFunc(int mode) {
    rgbmat->showNum(mode, 3);
}

bool leftFunc() {
    return bitRead(rgblf->getPositionState(), 1);
}

bool rigftFunc() {
    return bitRead(rgblf->getPositionState(), 2);
}

void task1() {
    Serial.println(F("executing task 1"));
    int movement_delay = 300;
    int normal_speed = 130;
    int degree_90 = 32;
    int degree_45 = 16;
    float braking_speed = 0.7f;

    delay(500);

    while (uls->distanceCm() < 20) {
        if (uls->distanceCm() > 10) {
            m->run(normal_speed + 25, normal_speed);
        } else {
            m->run(normal_speed, normal_speed + 25);
        }
    }
    m->run(0, 0);

    delay(movement_delay);
    fm->run(15, -normal_speed, -normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(degree_90, 0, normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(degree_45, 0, normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(60, -normal_speed, -normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(degree_90, 0, -normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(degree_45, 0, -normal_speed, braking_speed);

    delay(5000);

    delay(movement_delay);
    fm->run(degree_90, 0, normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(degree_45, 0, normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(60, normal_speed, normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(degree_90, 0, -normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(degree_45, 0, -normal_speed, braking_speed);
    delay(movement_delay);
    fm->run(60, normal_speed, normal_speed, braking_speed);
    for (;;) {
    }
}

void task2() {
    Serial.println(F("executing task 2"));

    int movement_delay = 100;
    int normal_speed = 130;
    float braking_speed = 0.7f;

    rgblf->setRGBColour(RGB_COLOUR_BLUE);
    rgblf->updataAllSensorValue();
    lf_algo->calculate(leftFunc(), rigftFunc());
    delay(100);
    while (rgblf->getPositionState() != B1111) {
        rgblf->updataAllSensorValue();
        lf_algo->calculate(leftFunc(), rigftFunc());
        m->run(lf_algo->get_m1(), lf_algo->get_m2());

        delay(10);
    }
    m->run(0, 0);
    delay(movement_delay);
    fm->run(30, -normal_speed, -normal_speed, braking_speed);
    delay(movement_delay);
    rgblf->updataAllSensorValue();
    while (rgblf->getPositionState() != B1111) {
        rgblf->updataAllSensorValue();
        lf_algo->calculate(leftFunc(), rigftFunc());
        m->run(lf_algo->get_m1(), lf_algo->get_m2());

        delay(10);
    }
    m->run(0, 0);
    delay(movement_delay);
    fm->run(50, -normal_speed, -normal_speed, braking_speed);
    int blockCount = 0;
    rgbmat->showNum(blockCount, 3);
    if (uls->distanceCm() < 50) {
        buzz->tone(1000, 100);
        blockCount++;
    }
    rgbmat->showNum(blockCount, 3);
    for (int j = 0; j <= 4; j++) {
        delay(movement_delay);
        fm->run(18, normal_speed, normal_speed, braking_speed);
        if (uls->distanceCm() < 50) {
            buzz->tone(1000, 100);
            blockCount++;
        }
        rgbmat->showNum(blockCount, 3);
    }
    rgbmat->showNum(blockCount, 3);
    for (;;) {
    }
}

void task3() {
    int movement_delay = 300;
    int normal_speed = 130;
    int degree_90 = 32;
    int degree_45 = 16;
    float braking_speed = 0.7f;

    rgblf->setRGBColour(RGB_COLOUR_BLUE);
    rgblf->updataAllSensorValue();
    lf_algo->calculate(leftFunc(), rigftFunc());
    delay(100);
    while (rgblf->getPositionState() != B1111) {
        rgblf->updataAllSensorValue();
        lf_algo->calculate(leftFunc(), rigftFunc());
        m->run(lf_algo->get_m1(), lf_algo->get_m2());

        delay(10);
    }
    m->run(0, 0);
    delay(movement_delay);
    m->run(130, 130);
    delay(200);
    m->run(0, 0);
    delay(movement_delay);
    rgblf->updataAllSensorValue();
    while (rgblf->getPositionState() != B1111) {
        rgblf->updataAllSensorValue();
        lf_algo->calculate(leftFunc(), rigftFunc());
        m->run(lf_algo->get_m1(), lf_algo->get_m2());

        delay(10);
    }
    m->run(0, 0);

    fm->run(25, normal_speed, normal_speed, braking_speed);
    fm->run(degree_90, 0, -normal_speed, braking_speed);

    rgblf->updataAllSensorValue();
    while (rgblf->getPositionState() != B1111) {
        rgblf->updataAllSensorValue();
        lf_algo->calculate(leftFunc(), rigftFunc());
        m->run(lf_algo->get_m1(), lf_algo->get_m2());

        delay(10);
    }
    m->run(0, 0);

    for (;;) {
    }
}

void task4() {
    Voltmeter volt(3, s1);
    m->run(255, 255);
    rgbmat->showNum(volt.readVolt());
    for (;;) {
        rgbmat->showNum(volt.readVolt());
        delay(500);
    }
}

void setup() {
    init_framework();

    rgbmat = new MeLEDMatrix(4);
    rgbmat->setColorIndex(1);
    rgbmat->setBrightness(6);
    rgbmat->showNum(2, 3);

    ModeFunc modeList[] = {
        (ModeFunc)task1,
        (ModeFunc)task2,
        (ModeFunc)task3,
        (ModeFunc)task4};

    fm = new felixmeter(2, s1);
    uls = new ultrasonic(1);
    led = new rgbled();
    m = new motor();
    rgblf = new rgblinefollower(3, 0);
    lf_algo = new LineFollowerAlgo();
    buzz = new buzzer();

    /*Voltmeter volt(3, s1);
    m->run(255, 255);
    rgbmat->showNum(volt.readVolt());
    for (;;) {
        rgbmat->showNum(volt.readVolt());
        delay(500);
    }*/
    mode = new ModeSelector((ModeDispCallback)modeDispFunc, modeList);

    //m = new motor();
    //m->run(255, 255);
    //volt = new Voltmeter(3, s1);

    //pid = new PID(0.1, 0.001, 0.005);
    //
    //fm->bindPID(pid);
    //fm->reaccurate();
    //fm->run(15, 0, 200, 100);
    //fm->run(31, 0, 200, 100);
}

void loop() {
}