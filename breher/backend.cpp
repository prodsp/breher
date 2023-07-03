#include "backend.h"
#include <QString>
#include "devices/valve.h"


Backend::Backend(QObject *parent) : QObject(parent)
{
    rspiSensor = new CurrentSensor(rspiSensorName,rspiSensorAddress,rspiSensorBus);

    deviceThread = new QThread();
    for(unsigned int i = 0; i < valveNumber; i++){

        valves[i] = new Valve(i);
        valves[i]->moveToThread(deviceThread);

        valvesState[i] = 1;
    }

    for(unsigned int i = 0; i < pumpNumber; i++){

        pumps[i] = new Pump(pumpGPIO[i]);
        pumpSensors[i] = new CurrentSensor(pumpSensorName,pumpSensorAddress[i],pumpSensorBus);

        pumps[i]->moveToThread(deviceThread);

    }

    for(unsigned int i = 0; i < solenoidNumber; i++){

        solenoids[i] = new Solenoid(solenoidGPIO[i]);
        solenoids[i]->moveToThread(deviceThread);

    }

    for(unsigned int i = 0; i < heaterNumber; i++){

        heaters[i] = new Heater(heaterGPIO[i]);
        tempSensors[i] = new TemperatureSensor(tempSensorName,tempSensorAddress[i],tempSensorBus);


        heaters[i]->moveToThread(deviceThread);

    }

    deviceThread->start();

}
Backend::~Backend(){

    delete rspiSensor;

    for(unsigned int i = 0; i < valveNumber; i++){
        delete valves[i];
    }
    for(unsigned int i = 0; i < pumpNumber; i++){
        delete pumps[i];
        delete pumpSensors[i];
    }
    for(unsigned int i = 0; i < heaterNumber; i++){
        delete heaters[i];
        delete tempSensors[i];
    }
    for(unsigned int i = 0; i < solenoidNumber; i++){
        delete solenoids[i];
    }

    deviceThread->exit();
    deviceThread->wait();
    delete deviceThread;

}




unsigned int Backend::getValveNumber(void){

    return valveNumber;
}

unsigned int Backend::getHeaterNumber(void){

    return heaterNumber;
}

unsigned int Backend::getPumpNumber(void){

    return pumpNumber;
}

unsigned int Backend::getSolenoidNumber(void){

    return solenoidNumber;
}

unsigned int Backend::getMaxNumberInSameType(void){
    unsigned int max1 = 0;
    unsigned int max2 = 0;
    if (valveNumber >= heaterNumber)
        max1 = valveNumber;
    else
        max1 = heaterNumber;

    if (solenoidNumber >= pumpNumber)
        max2 = solenoidNumber;
    else
        max2= pumpNumber;

    if(max1 >= max2)
        return max1;
    else
        return max2;

}

unsigned int Backend::getValveState(unsigned int index){

    return valvesState[index];
}
void Backend::setValveState(unsigned int index,unsigned int state){
    connect(this,&Backend::openValve,valves[index],&Valve::open);
    connect(this,&Backend::closeValve,valves[index],&Valve::close);


    if(state == 0)
        emit openValve();
    else
        emit closeValve();
    // QThread::msleep(200);
    valvesState[index] = state;

    disconnect(this,&Backend::openValve,valves[index],&Valve::open);
    disconnect(this,&Backend::closeValve,valves[index],&Valve::close);
    emit valveStateChanged(index,state);
}

void Backend::setValveStrength(unsigned int index, int strength){
    connect(this,&Backend::changeValveStrength,valves[index],&Valve::setStrength);

    if(strength == 0)
        valvesState[index] = 0;
    else
        valvesState[index] = 1;

    emit changeValveStrength(strength);

    disconnect(this,&Backend::changeValveStrength,valves[index],&Valve::setStrength);
    emit valveStateChanged(index,strength);
}

unsigned int Backend::getHeaterState(unsigned int index){

    return heaterState[index];
}
void Backend::setHeaterState(unsigned int index,unsigned int state){
    connect(this,&Backend::setHeater,heaters[index],&Heater::setState);

    bool temp = false;
    if(state)
        temp = true;

    emit setHeater(temp);
    //QThread::msleep(200);
    heaterState[index] = temp;

    disconnect(this,&Backend::setHeater,heaters[index],&Heater::setState);
    emit heaterStateChanged(index,state);
}


unsigned int Backend::getSolenoidState(unsigned int index){

    return solenoidState[index];
}
void Backend::setSolenoidState(unsigned int index,unsigned int state){
    connect(this,&Backend::setSolenoid,solenoids[index],&Solenoid::setState);

    bool temp = false;
    if(state)
        temp = true;

    emit setSolenoid(temp);
    //QThread::msleep(200);
    solenoidState[index] = temp;

    disconnect(this,&Backend::setSolenoid,solenoids[index],&Solenoid::setState);
    emit solenoidStateChanged(index,state);
}

unsigned int Backend::getPumpState(unsigned int index){

    return pumpState[index];
}
void Backend::setPumpState(unsigned int index,unsigned int state){
    connect(this,&Backend::setPump,pumps[index],&Pump::setState);

    bool temp = false;
    if(state)
        temp = true;

    emit setPump(temp);
    //QThread::msleep(200);
    pumpState[index] = temp;

    disconnect(this,&Backend::setPump,pumps[index],&Pump::setState);
    emit pumpStateChanged(index,state);
}

double Backend::getRaspCurrent(void){
    return rspiSensor->getCurrent();
}
double Backend::getRaspPower(void){
    return rspiSensor->getPower();
}

double Backend::getRaspOutputVoltage(void){
    return rspiSensor->getOutputVoltage();
}

double Backend::getRaspInputVoltage(void){
    return rspiSensor->getInputVoltage();
}
double Backend::getPumpCurrent(unsigned int index){
    return pumpSensors[index]->getCurrent();
}
double Backend::getPumpPower(unsigned int index){
    return pumpSensors[index]->getPower();
}
double Backend::getPumpOutputVoltage(unsigned int index){
    return pumpSensors[index]->getOutputVoltage();
}
double Backend::getPumpInputVoltage(unsigned int index){
    return pumpSensors[index]->getInputVoltage();
}

double Backend::getTemperature(unsigned int index){
    return tempSensors[index]->getTemperature();
}
