#include "gpio.h"
#include "utils.h"
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

Gpio::Gpio()
{

}

Gpio::Gpio(int pin)
{
    /* try to open sysfs files multiple times before giving up */
    int retryCount=SYSFS_RETRYCOUNT;
    while(retryCount){
        if(driverExport(pin)){
            break;
        } else{
            retryCount--;
            std::this_thread::sleep_for(std::chrono::milliseconds(SYSFS_RETRYPERIOD));
        }
    }
    if(!retryCount){
        throw "failed to open export file";
    }

    retryCount=SYSFS_RETRYCOUNT;
    while(retryCount){
        if(setDir(true)){
            break;
        } else{
            retryCount--;
            std::this_thread::sleep_for(std::chrono::milliseconds(SYSFS_RETRYPERIOD));
        }
    }
    if(!retryCount){
        throw "failed to open dir file";
    }

    retryCount=SYSFS_RETRYCOUNT;
    while(retryCount){
        if(setState(false)){
            break;
        } else{
            retryCount--;
            std::this_thread::sleep_for(std::chrono::milliseconds(SYSFS_RETRYPERIOD));
        }
    }
    if(!retryCount){
        std::cout << "ajjajj" << std::endl;
        throw "failed to initialize GPIO";
    }
}

bool Gpio::setState(bool state)
{
    std::ofstream valueFile_Handler;
    valueFile_Handler.open(format(GPIO_SYSFS_VALUE_PATH,m_pin));
    if(valueFile_Handler){
        valueFile_Handler << std::to_string(state) << std::endl;
        valueFile_Handler.flush();
        valueFile_Handler.close();
        m_state=state;
        return true;
    } else {
        std::cout << "WARNING: failed to open GPIO value file" << std::endl;
        return false;
    }
}


bool Gpio::driverExport(int pin)
{
    std::ofstream exportFile_Handler;
    exportFile_Handler.open(GPIO_SYSFS_EXPORT_PATH);
    if(exportFile_Handler){

        exportFile_Handler << std::to_string(pin) << std::endl;
        exportFile_Handler.flush();
        exportFile_Handler.close();
        m_pin=pin;
        return true;
    } else{
        std::cout << "WARNING: failed to open GPIO export file" << std::endl;
        return false;
    }
}
bool Gpio::driverUnexport()
{
    std::ofstream unexportFile_Handler;
    unexportFile_Handler.open(GPIO_SYSFS_UNEXPORT_PATH);
    if(unexportFile_Handler){
        unexportFile_Handler << std::to_string(m_pin) << std::endl;
        unexportFile_Handler.flush();
        unexportFile_Handler.close();
        return true;
    } else {
        std::cout << "WARNING: failed to open GPIO unexport file" << std::endl;
        return false;
    }
}
bool Gpio::setDir(bool dir)
{
    std::ofstream dirFile_Handler;
    dirFile_Handler.open(format(GPIO_SYSFS_DIR_PATH,m_pin));
    if(dirFile_Handler) {
        dirFile_Handler << "out" << std::endl;
        dirFile_Handler.flush();
        dirFile_Handler.close();
        m_dir=dir;
        return true;
    } else {
        std::cout << "WARNING: failed to open GPIO dir file" << std::endl;
        return false;
    }
}

Gpio::~Gpio()
{
    int retryCount=SYSFS_RETRYCOUNT;
    while(retryCount){
        if(setState(false)){
            break;
        } else{
            retryCount--;
            std::this_thread::sleep_for(std::chrono::milliseconds(SYSFS_RETRYPERIOD));
        }
    }
    retryCount=SYSFS_RETRYCOUNT;
    while(retryCount){
        if(driverUnexport()){
            break;
        } else{
            retryCount--;
            std::this_thread::sleep_for(std::chrono::milliseconds(SYSFS_RETRYPERIOD));
        }
    }
}
