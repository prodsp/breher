#ifndef VALVE_H
#define VALVE_H

#include "gpio.h"

class Valve : public Gpio
{
    using Gpio::Gpio;
public:
    Valve();
    void open();
    void close();
};

#endif // VALVE_H
