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

    bool systemTime(QString &startup, QString &free);
    bool diskRate(long &read, long &write);
    void netRate(long &netDown, long &netUpload);
    void cpuRate(long &cpuAll, long &cpuFree);
    void memoryRate(long &memory, long &memoryAll, long &swap, long &swapAll);
    QString setRateUnitSensitive(RateUnit unit, Sensitive sensitive = SpeedInfo::Default);
    double autoRateUnits(long speed, RateUnit &unit);
};

#endif // SPEEDINFO_H
