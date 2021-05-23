#include "mode_selector.h"

ModeSelector::ModeSelector(ModeDispCallback modeDispCallback, ModeFunc funcList[]) : button() {
    int LastTime = millis();
    int choice = 0;

    while ((millis() - LastTime) < 500 || choice == 0) {
        modeDispCallback(choice);

        if (button::is_pressed()) {
            delay(50);
            while (button::is_pressed()) {
            }
            choice++;
            LastTime = millis();
        }
    }

    funcList[choice - 1]();
}
