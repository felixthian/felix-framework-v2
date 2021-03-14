#ifndef RGBLED_H_
#define RGBLED_H_

#include <Arduino.h>

#include <FastLED.h>

enum sides { left, right };

class rgbled {
   public:
    rgbled();
    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    void setColor(sides side, uint8_t red, uint8_t green, uint8_t blue);

   private:
    CRGB led[2];
};

#endif