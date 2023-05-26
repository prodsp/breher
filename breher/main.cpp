#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "gpio.h"
#include "pump.h"
#include "heater.h"
#include "solenoid.h"
#include "valve.h"


constexpr int VALVE_COUNT = 2;
constexpr int PUMP_COUNT = 2;
constexpr int HEATER_COUNT = 2;
constexpr int SOLENOID_COUNT = 1;

Valve* valves[VALVE_COUNT];
Pump* pumps[PUMP_COUNT];
Heater* heaters[HEATER_COUNT];
Solenoid* solenoids[SOLENOID_COUNT];


void valveMenu()
{
    std::cout<<"0-9"<<std::endl;
    int instance;
    char action;
    std::cin>>instance;
    std::cout<<"o - open; x - close"<< std::endl;
    std::cin>>action;
    switch (action){
    case 'o': valves[instance]->open(); break;
    case 'x': valves[instance]->close(); break;
    }
}
void pumpMenu()
{
    std::cout<<"0-1"<<std::endl;
    int instance;
    char action;
    std::cin>>instance;
    std::cout<<"o - start; x - stop"<< std::endl;
    std::cin>>action;
    switch (action){
    case 'o': pumps[instance]->setState(true); break;
    case 'x': pumps[instance]->setState(false); break;
    }
}
void heaterMenu()
{
    std::cout<<"0-1"<<std::endl;
    int instance;
    char action;
    std::cin>>instance;
    std::cout<<"o - start; x - stop"<< std::endl;
    std::cin>>action;
    switch (action){
    case 'o': heaters[instance]->setState(true); break;
    case 'x': heaters[instance]->setState(false); break;
    }
}
void solenoidMenu()
{
    std::cout<<"0"<<std::endl;
    int instance;
    char action;
    std::cin>>instance;
    std::cout<<"o - open; x - close"<< std::endl;
    std::cin>>action;
    switch (action){
    case 'o': solenoids[instance]->setState(true); break;
    case 'x': solenoids[instance]->setState(false); break;
    }
}


void mainMenu()
{
    char yourchoice;
    bool running=true;

    while(running){
        std::cout<<"v - valve; p - pump; h - heater; s - solenoid; q - quit"<<std::endl;
        std::cin>>yourchoice;
        switch (yourchoice)
        {
        case 'v': valveMenu(); break;
        case 'p': pumpMenu();break;
        case 'h': heaterMenu(); break;
        case 's': solenoidMenu(); break;
        case 'q': running=false; break;
        default: std::cout<<"invalid"; break;
        }
    }
}


int main()
{
    try {
        for(int ii=0; ii<VALVE_COUNT; ii++){
            valves[ii] = new Valve(ii);
        }
        pumps[0] = new Pump(13);
        pumps[1] = new Pump(19);
        heaters[0] = new Heater(16);
        heaters[1] = new Heater(26);
        solenoids[0] = new Solenoid(20);

    } catch (const char* e) {
        std::cout << "Failed to init device " << e << std::endl;
        return -1;
    }


    mainMenu();


    for(int ii=0; ii<PUMP_COUNT; ii++){
        delete pumps[ii];
    }
    for(int ii=0; ii<HEATER_COUNT; ii++){
        delete heaters[ii];
    }
    for(int ii=0; ii<SOLENOID_COUNT; ii++){
        delete solenoids[ii];
    }
    for(int ii=0; ii<VALVE_COUNT; ii++){
        delete valves[ii];
    }

    return 0;
}
