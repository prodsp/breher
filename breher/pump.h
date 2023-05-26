#ifndef PUMP_H
#define PUMP_H

#include "gpio.h"

class Pump : public Gpio
{
    using Gpio::Gpio;
public:
    Pump();
    void start();
    void stop();
};

#endif // PUMP_H
