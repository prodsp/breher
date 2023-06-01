#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <unistd.h>
#include <termios.h>

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

/*!  linux platform specific code,
 * to read single character input 
 * without pressing the return key */
char getch() {
        char buf = 0;
        struct termios old = {};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

int validateChoise(char instance,int limit)
{
    int validInstance = static_cast<int>(instance);
    validInstance-='0';
    if(validInstance>=limit) validInstance=limit-1;
    if(validInstance<0) validInstance=0;
    return validInstance;
}

void valveMenu()
{
    std::cout<<"0-"<<VALVE_COUNT-1<<std::endl;
    int instance=validateChoise(getch(),VALVE_COUNT);
    std::cout<<"o - open; x - close"<< std::endl;
    switch (getch()){
        case 'o': valves[instance]->open(); break;
        case 'x': valves[instance]->close(); break;
        default: std::cout<<"invalid"<<std::endl; break;
    }
}

void pumpMenu()
{
    std::cout<<"0-"<<PUMP_COUNT-1<<std::endl;
    int instance=validateChoise(getch(),PUMP_COUNT);
    std::cout<<"o - start; x - stop"<< std::endl;
    switch (getch()){
        case 'o': pumps[instance]->setState(true); break;
        case 'x': pumps[instance]->setState(false); break;
        default: std::cout<<"invalid"<<std::endl; break;
    }
}

void heaterMenu()
{
    std::cout<<"0-"<<HEATER_COUNT-1<<std::endl;
    int instance=validateChoise(getch(),HEATER_COUNT);
    std::cout<<"o - start; x - stop"<< std::endl;
    switch (getch()){
        case 'o': heaters[instance]->setState(true); break;
        case 'x': heaters[instance]->setState(false); break;
        default: std::cout<<"invalid"<<std::endl; break;
    }
}

void solenoidMenu()
{
    std::cout<<"0-"<<SOLENOID_COUNT-1<<std::endl;
    int instance=validateChoise(getch(),SOLENOID_COUNT);
    std::cout<<"o - open; x - close"<< std::endl;
    switch (getch()){
        case 'o': solenoids[instance]->setState(true); break;
        case 'x': solenoids[instance]->setState(false); break;
        default: std::cout<<"invalid"<<std::endl; break;
    }
}

void mainMenu()
{
    bool running=true;

    while(running){
        std::cout<<"v - valve; p - pump; h - heater; s - solenoid; q - quit"<<std::endl;
        switch (getch())
        {
        case 'v': valveMenu(); break;
        case 'p': pumpMenu();break;
        case 'h': heaterMenu(); break;
        case 's': solenoidMenu(); break;
        case 'q': running=false; break;
        default: std::cout<<"invalid"<<std::endl; break;
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
