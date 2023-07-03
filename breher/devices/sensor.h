#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include <QTimer>
#include "sensors/sensors.h"
#include "sensors/error.h"

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit Sensor(QString name, int address, int busNumber, QObject *parent = nullptr);
    QString getName(void);
    QString getAddress(void);
    QString getBusNumber(void);
    double  getFeatureValue(QString featureName);


private:
    QString name;
    int address;
    int busNumber;
signals:

};


class CurrentSensor : public Sensor
{
public:
    explicit CurrentSensor(QString name, int address, int busNumber, QObject *parent = nullptr) : Sensor(name, address, busNumber, parent){};
    double getCurrent(void);
    double getPower(void);
    double getInputVoltage(void);
    double getOutputVoltage(void);
};


class TemperatureSensor : public Sensor
{
public:
    explicit TemperatureSensor(QString name, int address, int busNumber, QObject *parent = nullptr) : Sensor(name, address, busNumber, parent){};
    double getTemperature(void);
};


#endif // SENSOR_H
