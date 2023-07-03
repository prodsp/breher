#ifndef HEATER_H
#define HEATER_H

#include "gpio.h"

class Heater : public Gpio
{
    using Gpio::Gpio;
public:
    Heater();
};

#endif // HEATER_H
