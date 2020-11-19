#include "speedinfo.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QThread>
#include <QtMath>
#include <QTimer>
#include <QDateTime>

#define PROC_PATH_UPTIME    "/proc/uptime"      // "系统启动" 和 "系统空闲" 的时间
#define PROC_PATH_CPU       "/proc/stat"        // "CPU" 使用率 的状态
#define PROC_PATH_MEM       "/proc/meminfo"     // "内存" 和 "交换空间" 的状态
#define PROC_PATH_NET       "/proc/net/dev"     // "网速" 下载和上传 的状态
#define PROC_PATH_DISK      "/proc/diskstats"   // "磁盘" 读取和写入 的状态

SpeedInfo::SpeedInfo(QObject *parent)
    :QObject(parent)
{
}

/*!
 * \brief SpeedInfo::cpuRate 获取某一次 CPU 的使用情况
 * \param[out] cpuAll 总 cpu 使用量
 * \param[out] cpuFree 空闲 cpu 的使用量
 */
void SpeedInfo::cpuRate(long &cpuAll, long &cpuFree)
{
    cpuAll = cpuFree = 0;
    bool ok = false;
    QFile file(PROC_PATH_CPU);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);
    QString line = stream.readLine();
    if (!line.isNull()) {
        QStringList list = line.split(QRegExp("\\s{1,}"));
        for (auto v = list.begin() + 1; v != list.end(); ++v)
            cpuAll += (*v).toLong(&ok);

        cpuFree = list.at(4).toLong(&ok);
    }

    file.close();
}

/*!
 * \brief SpeedInfo::memoryRate 获取 “内存” 和 “交换空间” 的某一时刻的使用情况
 * \param memory 内存使用量
 * \param memoryAll 内存总量
 * \param swap 交换空间使用量
 * \param swapAll 交换空间总量
 */
void SpeedInfo::memoryRate(long &memory, long &memoryAll, long &swap, long &swapAll)
{
    memory = memoryAll = 0;
    swap = swapAll = 0;
    bool ok = false;
    QFile file(PROC_PATH_MEM);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream stream(&file);
    long buff[16] = {0};
    for (int i = 0; i <= 15; ++i) {
        QString line = stream.readLine();
        QStringList list = line.split(QRegExp("\\s{1,}"));
        buff[i] = list.at(1).toLong(&ok);

    }

    memoryAll = buff[0];
    memory = buff[0] - buff[2];
    swapAll = buff[14];
    swap = buff[14] - buff[15];

    file.close();
}

/*!
 * \brief SpeedInfo::netRate 获取网某一时刻的网络总的数据包量
 * \param[out] netUpload 网络上传数据量
 * \param[out] netUpload 网络下载数据量
 * \return 是否获取网络速率成功
 */
void SpeedInfo::netRate(long &netDown, long &netUpload)
{
    QFile file(PROC_PATH_NET);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // 在读取时，把行尾结束符修改为 '\n'； 在写入时，把行尾结束符修改为本地系统换行风格，比如Windows文本换行是 "\r\n"
        qDebug()<<"\"/proc/net/dev\" don't open!";
        return;
    }

    long down = 0;
    long upload = 0;
    QTextStream stream(&file);
    QString line = stream.readLine();
    line  = stream.readLine();
    line  = stream.readLine();
    while (!line.isNull()) {
        QStringList list = line.split(QRegExp("\\s{1,}"));   // 匹配任意 大于等于1个的 空白字符

        if (!list.isEmpty()) {
            down = list.at(2).toLong();
            upload = list.at(10).toLong();
        }

        netDown += down;
        netUpload += upload;
        line  = stream.readLine();
    }

    file.close();
}

/*!
 * \brief SpeedInfo::setRateUnitSensitive 设置速率单位的大小写模式
 * \param[in] unit 传入进来的网速单位
 * \param sensitive 设置的速率单位大小写模式
 * \return 速率单位字符串
 */
QString SpeedInfo::setRateUnitSensitive(RateUnit unit, Sensitive sensitive)
{
    switch (sensitive) {
    case Sensitive::Default: {
        switch (unit) {
        case RateUnit::RateBit:
            return QString("b/s");
        case RateUnit::RateByte:
            return QString("B/s");
        case RateUnit::RateKb:
            return QString("Kb/s");
        case RateUnit::RateMb:
            return QString("Mb/s");
        case RateUnit::RateGb:
            return QString("Gb/s");
        case RateUnit::RateTb:
            return QString("Tb/s");
        default:
            qDebug()<<QString("Sensitive::Default,  RateUnit is RateUnknow.");
            return QString("");
        }
    }
    case Sensitive::Upper: {
        switch (unit) {
        case RateUnit::RateBit:
            return QString("BIT/S");
        case RateUnit::RateByte:
            return QString("BYTE/S");
        case RateUnit::RateKb:
            return QString("KB/S");
        case RateUnit::RateMb:
            return QString("MB/S");
        case RateUnit::RateGb:
            return QString("GB/S");
        case RateUnit::RateTb:
            return QString("TB/S");
        default:
            qDebug()<<QString("Sensitive::Upper,  RateUnit is RateUnknow.");
            return QString("");
        }
    }
    case Sensitive::Lower: {
        switch (unit) {
        case RateUnit::RateBit:
            return QString("bit/s");
        case RateUnit::RateByte:
            return QString("byte/s");
        case RateUnit::RateKb:
            return QString("kb/s");
        case RateUnit::RateMb:
            return QString("mb/s");
        case RateUnit::RateGb:
            return QString("gb/s");
        case RateUnit::RateTb:
            return QString("tb/s");
        default:
            qDebug()<<QString("Sensitive::Lower,  RateUnit is RateUnknow.");
            return QString("");
        }
    }
    default: {
        qDebug()<<QString("Sensitive is RateUnknow.");
        return QString("");
    }
    }
}

/*!
 * \brief SpeedInfo::autoRateUnits 自动显示单位
 * \param[in] speed 传入的网速(无单位)
 * \param[out] unit 智能调节后的网速的单位
 * \param sensitive 速率单位的大小写模式
 * \return 自能调节单位后的速率
 */
double SpeedInfo::autoRateUnits(long speed, SpeedInfo::RateUnit &unit)
{
    /* 自动判断合适的速率单位,默认传进来的是 Byte
     * bit    0 ~ 7 位 (不到 1 字节)
     * Byte   1    ~ 2^10  Byte
     * KB     2^10 ~ 2^20  Byte
     * MB     2^20 ~ 2^30  Byte
     * GB     2^30 ~ 2^40  Byte
     * TB     2^40 ~ 2^50  Byte
     */

    if (unit != SpeedInfo::RateByte) {
        qDebug()<<"请先将单位转为字节(byte)后再传参";
        return -1;
    }

    double sp = 0;
    if (0 <= speed && speed < qPow(2, 10)) {
        unit = SpeedInfo::RateByte;
        sp = speed;
    } else if (qPow(2, 10) <= speed && speed < qPow(2, 20)) {
        unit = SpeedInfo::RateKb;
        sp = static_cast<double>(speed / qPow(2, 10) * 1.0);
    } else if (qPow(2, 20) <= speed && speed < qPow(2, 30)) {
        unit = SpeedInfo::RateMb;
        sp = static_cast<double>(speed / qPow(2, 20) * 1.0);
    } else if (qPow(2, 30) <= speed && speed < qPow(2, 40)) {
        unit = SpeedInfo::RateGb;
        sp = static_cast<double>(speed / qPow(2, 30) * 1.0);
    } else if (qPow(2, 40) <= speed && speed < qPow(2, 50)) {
        unit = SpeedInfo::RateTb;
        sp = static_cast<double>(speed / qPow(2, 40) * 1.0);
    } else {
        unit = SpeedInfo::RateUnknow;
        qDebug()<<"本设备网络速率单位传输超过 TB, 或者低于 0 Byte.";
        sp = -1;
    }

//    qDebug()<<"-------->sp:"<<sp<<"    "<<"speed:"<<speed<<"   unit:"<<unit;
    return sp;
}


