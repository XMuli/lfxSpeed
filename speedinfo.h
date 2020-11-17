#ifndef SPEEDINFO_H
#define SPEEDINFO_H

#include <QObject>

class QString;
class QTimer;

class SpeedInfo: public QObject
{
    Q_OBJECT
public:
    enum RateUnit {
        RateBit,
        RateByte,
        RateKb,
        RateMb,
        RateGb,
        RateTb,
        RateUnknow
    };
    Q_ENUM(RateUnit)

    enum Sensitive {
        Default,  // 大小写混合
        Upper,    // 全部大写
        Lower     // 全部小写
    };

public:
    SpeedInfo(QObject *parent = nullptr);

    void init();
    bool systemTime(QString &startup, QString &free);
    bool cpuRate(long &cpu);
    bool memoryRate(long &memory, long &swap);
    bool diskRate(long &read, long &write);
    void netRate(double &down, double &upload, QString &downUnit, QString &uploadUnit, int decimalsNum = 2, int ms = 1000, Sensitive sensitive = SpeedInfo::Default);

private:
    bool netRate(long &netDown, long &netUpload);
    QString setRateUnitSensitive(RateUnit unit, Sensitive sensitive = SpeedInfo::Default);
    double autoRateUnits(long speed, RateUnit &unit);

private:
    QTimer *m_timer;
};

#endif // SPEEDINFO_H
