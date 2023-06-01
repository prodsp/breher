#ifndef SOLENOID_H
#define SOLENOID_H

#include "gpio.h"

class Solenoid : public Gpio
{
    using Gpio::Gpio;
public:
    Solenoid();
    void open();
    void close();
};

#endif // SOLENOID_H
