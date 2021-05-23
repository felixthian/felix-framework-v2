#include "rgbled.h"

#include "config.h"

rgbled::rgbled() {
    FastLED.addLeds<WS2812, 13, GRB>(led, 2);
}

void rgbled::setColor(uint8_t red, uint8_t green, uint8_t blue) {
#ifdef DEBUG
    debug->log_no_newline(F("reload rgb led data by bit banging "));
#endif
    led[0] = CRGB(red, green, blue);
    led[1] = led[0];
    FastLED.show();
#ifdef DEBUG
    debug->log(F("[OK]"));
#endif
}

void rgbled::setColor(sides side, uint8_t red, uint8_t green, uint8_t blue) {
#ifdef DEBUG
    debug->log_no_newline(F("reload rgb led data by bit banging..."));
#endif
    if (side == left) {
        led[0] = CRGB(red, green, blue);
        FastLED.show();
    } else if (side == right) {
        led[1] = CRGB(red, green, blue);
        FastLED.show();
    }
#ifdef DEBUG
    debug->log(F("[OK]"));
#endif
}