#include <iostream>
#include <chrono>
#include <thread>

#include "gpio.h"
#include "pump.h"
#include "heater.h"
#include "solenoid.h"
#include "valve.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    Pump* mashPump;
    Pump* boilPump;

    Heater* mashHeater;
    Heater* boilHeater;

    Solenoid* coolingWaterInlet;

    Valve* testValve;

    try {
        mashPump = new Pump(13);
        boilPump = new Pump(19);
        mashHeater = new Heater(16);
        boilHeater = new Heater(26);
        coolingWaterInlet = new Solenoid(20);
        testValve = new Valve(0);
    } catch (const char* e) {
        std::cout << "Failed to init device " << e << std::endl;
        return -1;
    }
    std::cout << "valve closed" << std::endl;

    /*
    mashPump->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    boilPump->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    mashHeater->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    boilHeater->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    coolingWaterInlet->setState(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    */

    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    //testValve->open();
    //std::cout << "valve opened" << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    testValve->setStrength(-10);
    testValve->setStrength(0);
    testValve->setStrength(10);
    testValve->setStrength(20);
    testValve->setStrength(50);
    testValve->setStrength(100);
    testValve->setStrength(1000);



    delete mashPump;
    delete boilPump;
    delete mashHeater;
    delete boilHeater;
    delete coolingWaterInlet;
    delete testValve;
    std::cout << "valve closed" << std::endl;

    return 0;
}
