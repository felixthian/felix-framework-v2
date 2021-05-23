#ifndef MODESELECTOR_H_
#define MODESELECTOR_H_

#include <Arduino.h>
#include "../hw/button.h"

typedef void (*ModeDispCallback)(int);

typedef void (*ModeFunc)(void);

class ModeSelector : private button{
   public:
    ModeSelector(ModeDispCallback modeDispCallback, ModeFunc funcList[]);
};

#endif