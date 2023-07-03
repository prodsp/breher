#include "valve.h"
#include "utils.h"
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

Valve::Valve()
{
}

Valve::Valve(int channel)
{
    int retryCount=PWM_SYSFS_RETRYCOUNT;
    while(retryCount){
        if(driverExport(channel)){
            break;
        } else{
            retryCount--;
            std::this_thread::sleep_for(std::chrono::milliseconds(PWM_SYSFS_RETRYPERIOD));
        }
    }
    if(!retryCount){
        throw "failed to open PWM export file";
    }


    retryCount=PWM_SYSFS_RETRYCOUNT;
    while(retryCount){
        if(setPeriod(PERIOD_50_HZ)){
            break;
        } else{
            retryCount--;
            std::this_thread::sleep_for(std::chrono::milliseconds(PWM_SYSFS_RETRYPERIOD));
        }
    }
    if(!retryCount){
        throw "failed to open PWM period file";
    }

    close();
}


bool Valve::driverExport(int channel)
{
    std::ofstream exportFile_Handler;
    exportFile_Handler.open(PWM_SYSFS_EXPORT_PATH);
    if(exportFile_Handler){
        exportFile_Handler << std::to_string(channel) << std::endl;
        exportFile_Handler.flush();
        exportFile_Handler.close();
        m_channel=channel;
        return true;
    } else{
        std::cout << "WARNING: failed to open PWM export file" << std::endl;
        return false;
    }
}

bool Valve::driverUnexport()
{
    std::ofstream unexportFile_Handler;
    unexportFile_Handler.open(PWM_SYSFS_UNEXPORT_PATH);
    if(unexportFile_Handler){
        unexportFile_Handler << std::to_string(m_channel) << std::endl;
        unexportFile_Handler.flush();
        unexportFile_Handler.close();
        return true;
    } else {
        std::cout << "WARNING: failed to open PWM unexport file" << std::endl;
        return false;
    }
}


bool Valve::setEnable(bool enable)
{
    std::ofstream file_Handler;
    file_Handler.open(format(PWM_SYSFS_ENABLE_PATH,m_channel));
    if(file_Handler){
        file_Handler << enable << std::endl;
        file_Handler.flush();
        file_Handler.close();
        return true;
    } else {
        std::cout << "WARNING: failed to open PWM enable file" << std::endl;
        return false;
    }
}
bool Valve::setPeriod(int period)
{
    std::ofstream file_Handler;
    file_Handler.open(format(PWM_SYSFS_PERIOD_PATH,m_channel));
    if(file_Handler){
        file_Handler << period << std::endl;
        file_Handler.flush();
        file_Handler.close();
        return true;
    } else {
        std::cout << "WARNING: failed to open PWM period file" << std::endl;
        return false;
    }
}
bool Valve::setDutyCycle(int duty)
{
    std::ofstream file_Handler;
    file_Handler.open(format(PWM_SYSFS_DUTY_PATH,m_channel));
    if(file_Handler){
        file_Handler << duty << std::endl;
        file_Handler.flush();
        file_Handler.close();
        return true;
    } else {
        std::cout << "WARNING: failed to open PWM duty_cycle file" << std::endl;
        return false;
    }
}

void Valve::open()
{
    setDutyCycle(DUTY_OPEN);
    setEnable(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(OPEN_DELAY_MS));
    setEnable(false);

    emit opened();
}

void Valve::close()
{
    setDutyCycle(DUTY_CLOSED);
    setEnable(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(CLOSE_DELAY_MS));
    setEnable(false);

    emit closed();
}

void Valve::setStrength(int strength)
{
    if(strength<STRENGTH_MIN) strength=STRENGTH_MIN;
    if(strength>STRENGTH_MAX) strength=STRENGTH_MAX;

    float closed = static_cast<float>(DUTY_CLOSED);
    float opened = static_cast<float>(DUTY_OPEN);
    float strength_f = static_cast<float>(strength);
    int duty = static_cast<int>(opened + strength_f*(closed-opened)/static_cast<float>(STRENGTH_MAX));
    //std::cout << "duty= " << duty << std::endl;

    setDutyCycle(duty);
    setEnable(true);
    std::this_thread::sleep_for(std::chrono::milliseconds(CLOSE_DELAY_MS));
    setEnable(false);

     emit strengthChanged(strength);
}

Valve::~Valve()
{
    close();
    driverUnexport();
}
