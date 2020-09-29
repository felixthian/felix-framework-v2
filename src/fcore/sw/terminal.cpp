#include "terminal.h"

#include "../hw/config.h"

terminal::terminal(int port_num, int felixmeter_port) : fserial(port_num), rgbled(), buzzer(), felixmeter(felixmeter_port) {
    fserial::write(F("Felix Framework V2.0\n(c) 2020 SMK Jalan Arang. All right reserved\n"));
    char receive[64];
    for (;;) {
        if (fserial::available()) {
            for (int v = 0; v < 64; v++) {
                receive[v] = '.';
            }
            delay(1000);
            char tmp = fserial::Read();
            int i = 0;
            while (tmp != (char)-1) {
                receive[i] = tmp;
                i++;
                tmp = fserial::Read();
            }
#ifdef DEBUG
            debug->log(receive);
#endif
            if (strstr(String(receive).c_str(), "forward")) {
                felixmeter::run(4, 120, 120);
            } else if (strstr(String(receive).c_str(), "backward")) {
                felixmeter::run(4, -120, -120);
            } else if (strstr(String(receive).c_str(), "left")) {
                felixmeter::run(7, 0, 120);
            } else if (strstr(String(receive).c_str(), "right")) {
                felixmeter::run(7, 0, -120);
            } else if (strstr(String(receive).c_str(), "tone")) {
                buzzer::tone(1000, 100);
            }
            buzzer::tone(1000, 100);
            fserial::flush();
        }
    }
}