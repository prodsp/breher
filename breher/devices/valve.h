#ifndef VALVE_H
#define VALVE_H
#include <QObject>

constexpr char PWM_SYSFS_EXPORT_PATH[] = "/sys/class/pwm/pwmchip0/export";
constexpr char PWM_SYSFS_UNEXPORT_PATH[] = "/sys/class/pwm/pwmchip0/unexport";
constexpr char PWM_SYSFS_ENABLE_PATH[] = "/sys/class/pwm/pwmchip0/pwm%d/enable";
constexpr char PWM_SYSFS_PERIOD_PATH[] = "/sys/class/pwm/pwmchip0/pwm%d/period";
constexpr char PWM_SYSFS_DUTY_PATH[] = "/sys/class/pwm/pwmchip0/pwm%d/duty_cycle";
constexpr int PWM_SYSFS_RETRYPERIOD = 100;
constexpr int PWM_SYSFS_RETRYCOUNT = 5;
constexpr int PERIOD_50_HZ = 20100000;
constexpr int DUTY_CLOSED = 2010000;
constexpr int DUTY_OPEN = 603000;
constexpr int OPEN_DELAY_MS = 2000;
constexpr int CLOSE_DELAY_MS = 5000;
constexpr int STRENGTH_MAX = 100;
constexpr int STRENGTH_MIN = 0;

class Valve : public QObject
{
 Q_OBJECT
private:
    bool driverExport(int channel);
    bool driverUnexport();
    int m_channel;
    bool m_state;
    bool setEnable(bool enable);
    bool setPeriod(int period);
    bool setDutyCycle(int duty);
public:
    Valve();
    ~Valve();
    Valve(int channel);


signals:
    void opened();
    void closed();
    void strengthChanged(int strength);

public slots:
    void open();
    void close();
    void setStrength(int strength);


};

#endif // VALVE_H
