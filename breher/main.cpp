#include <iostream>
#include <chrono>
#include <thread>

#include "gpio.h"
#include "pump.h"
#include "heater.h"
#include "solenoid.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Pump* mashPump;
    Pump* boilPump;

    Heater* mashHeater;
    Heater* boilHeater;

    Solenoid* coolingWaterInlet;

    try {
        mashPump = new Pump(13);
        boilPump = new Pump(19);
        mashHeater = new Heater(16);
        boilHeater = new Heater(26);
        coolingWaterInlet = new Solenoid(20);
    } catch (const char* e) {
        std::cout << "Failed to init device " << e << std::endl;
        return -1;
    }

    mashPump->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    boilPump->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    mashHeater->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    boilHeater->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    coolingWaterInlet->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));


    delete mashPump;
    delete boilPump;
    delete mashHeater;
    delete boilHeater;
    delete coolingWaterInlet;

    return 0;
}
