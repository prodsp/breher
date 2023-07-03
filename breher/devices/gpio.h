#ifndef GPIO_H
#define GPIO_H
#include <QObject>

constexpr char GPIO_SYSFS_EXPORT_PATH[] = "/sys/class/gpio/export";
constexpr char GPIO_SYSFS_UNEXPORT_PATH[] = "/sys/class/gpio/unexport";
constexpr char GPIO_SYSFS_DIR_PATH[] = "/sys/class/gpio/gpio%d/direction";
constexpr char GPIO_SYSFS_VALUE_PATH[] = "/sys/class/gpio/gpio%d/value";
constexpr int SYSFS_RETRYPERIOD = 100;
constexpr int SYSFS_RETRYCOUNT = 5;
class Gpio : public QObject
{
Q_OBJECT
private:
    int m_pin;
    bool m_state;
    bool m_dir;
    bool driverExport(int pin);
    bool driverUnexport();
    bool setDir(bool dir);
public:
    Gpio();
    ~Gpio();
    Gpio(int pin);
public slots:
    bool setState(bool state);
signals:
    void stateSet(bool);
};

#endif // GPIO_H
