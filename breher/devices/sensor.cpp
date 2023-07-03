#include "sensor.h"



Sensor::Sensor(QString name, int address, int busNumber, QObject *parent) : QObject(parent)
{

    int error = sensors_init(NULL);
    const sensors_chip_name *temp_chip;
    int chip_nr = 0;
    if(error == 0){
        while ((temp_chip = sensors_get_detected_chips(NULL, &chip_nr))) {
            if((name == temp_chip->prefix) && address == temp_chip->addr && busNumber == temp_chip->bus.nr){
                this->name = QString::fromStdString(temp_chip->prefix);
                this->address = temp_chip->addr;
                this->busNumber = temp_chip->bus.nr;

                break;
            }

        }
    }
    sensors_cleanup();
}

double Sensor::getFeatureValue(QString featureName){


    int error = sensors_init(NULL);
    const sensors_chip_name *temp_chip;
    int chip_nr = 0;

    double  value = qQNaN();
    QString errorStr = "";

    if(error == 0){
        while ((temp_chip = sensors_get_detected_chips(NULL, &chip_nr))) {
            if((name == temp_chip->prefix) && address == temp_chip->addr && busNumber == temp_chip->bus.nr){
                int feature_nr = 0;
                const sensors_feature* feature;
                while((feature = sensors_get_features(temp_chip,&feature_nr))){
                    if(feature->name == featureName){
                      error = sensors_get_value(temp_chip,feature->first_subfeature,&value);
                      break;
                    }
                }
            }
        }
    }


    errorStr = sensors_strerror(error);
    sensors_cleanup();
    return value;
}

double CurrentSensor::getInputVoltage(void){
    return this->getFeatureValue("in0");
}

double CurrentSensor::getOutputVoltage(void){
    return this->getFeatureValue("in1");
}

double CurrentSensor::getPower(void){
    return this->getFeatureValue("power1");
}

double CurrentSensor::getCurrent(void){
    return this->getFeatureValue("curr1");
}
double TemperatureSensor::getTemperature(void){
    return this->getFeatureValue("temp1");
}
