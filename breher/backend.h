#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <qqml.h>
#include <QThread>
#include"devices/valve.h"
#include"devices/pump.h"
#include"devices/solenoid.h"
#include"devices/heater.h"
#include"devices/sensor.h"

constexpr unsigned int valveNumber =  4;//10;
constexpr unsigned int pumpNumber = 2;
constexpr unsigned int heaterNumber = 2;
constexpr unsigned int solenoidNumber = 1;

constexpr unsigned int pumpGPIO[2] = {13,19};
constexpr unsigned int heaterGPIO[2] = {16,26};
constexpr unsigned int solenoidGPIO[1] = {20};


constexpr unsigned int rspiSensorAddress = 0x41;
constexpr unsigned int rspiSensorBus = 1;
constexpr char         rspiSensorName[] = "ina219";
constexpr unsigned int pumpSensorAddress[2] = {0x44,0x45};
constexpr unsigned int pumpSensorBus = 1;
constexpr char         pumpSensorName[] = "ina219";
constexpr unsigned int tempSensorAddress[2] = {0x4a,0x4b};
constexpr unsigned int tempSensorBus = 0;
constexpr char         tempSensorName[] = "sts3x";

class Backend : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString getLabel READ getLabel)
    //Q_PROPERTY(unsigned int valveState READ getValveState WRITE setValveState NOTIFY valveStateChanged)
    QML_ELEMENT



public:

    explicit Backend(QObject *parent = nullptr);
    ~Backend();

    Q_INVOKABLE  unsigned int getValveNumber(void);
    Q_INVOKABLE  unsigned int getValveState(unsigned int index);
    Q_INVOKABLE  void setValveState(unsigned int index,unsigned int state);
    Q_INVOKABLE  void setValveStrength(unsigned int index,int strength);

    Q_INVOKABLE  unsigned int getHeaterNumber(void);
    Q_INVOKABLE  unsigned int getHeaterState(unsigned int index);
    Q_INVOKABLE  void setHeaterState(unsigned int index,unsigned int state);

    Q_INVOKABLE  unsigned int getSolenoidNumber(void);
    Q_INVOKABLE  unsigned int getSolenoidState(unsigned int index);
    Q_INVOKABLE  void setSolenoidState(unsigned int index,unsigned int state);

    Q_INVOKABLE  unsigned int getPumpNumber(void);
    Q_INVOKABLE  unsigned int getPumpState(unsigned int index);
    Q_INVOKABLE  void setPumpState(unsigned int index,unsigned int state);

    Q_INVOKABLE  unsigned int getMaxNumberInSameType(void);

    Q_INVOKABLE  double getRaspCurrent(void);
    Q_INVOKABLE  double getRaspPower(void);
    Q_INVOKABLE  double getRaspOutputVoltage(void);
    Q_INVOKABLE  double getRaspInputVoltage(void);

    Q_INVOKABLE  double getPumpCurrent(unsigned int index);
    Q_INVOKABLE  double getPumpPower(unsigned int index);
    Q_INVOKABLE  double getPumpOutputVoltage(unsigned int index);
    Q_INVOKABLE  double getPumpInputVoltage(unsigned int index);

    Q_INVOKABLE  double getTemperature(unsigned int index);

private:
    CurrentSensor* rspiSensor;

    Valve* valves[valveNumber];
    unsigned int valvesState[valveNumber];

    Pump*  pumps[pumpNumber];
    unsigned int pumpState[pumpNumber];
    CurrentSensor* pumpSensors[pumpNumber];

    Solenoid* solenoids[solenoidNumber];
    unsigned int solenoidState[solenoidNumber];


    Heater *heaters[heaterNumber];
    unsigned int heaterState[heaterNumber];
    TemperatureSensor* tempSensors[heaterNumber];

    QThread*  deviceThread;
signals:

    void openValve();
    void closeValve();
    void changeValveStrength(int strength);

    void setHeater(bool state);
    void setPump(bool state);
    void setSolenoid(bool state);

    void valveStateChanged(unsigned int index,int strength);
    void heaterStateChanged(unsigned int index,unsigned int state);
    void pumpStateChanged(unsigned int index,unsigned int state);
    void solenoidStateChanged(unsigned int index,unsigned int state);
public slots:


};

#endif // BACKEND_H
