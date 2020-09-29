#ifndef PORT_H_
#define PORT_H_

#include <Arduino.h>

typedef struct {
    uint8_t s1;
    uint8_t s2;
} port_t;

#define read_error 9487

extern const port_t port_sig[4];
extern const bool s1;
extern const bool s2;

class port {
   public:
    port(int num);
    void dwrite(bool pin, bool data);
    int dread(bool pin);
    int dpread(bool pin);
    void awrite(bool pin, uint8_t data);
    int aread(bool pin);
    port_t get_port();

   protected:
    port_t pin;
};

#endif