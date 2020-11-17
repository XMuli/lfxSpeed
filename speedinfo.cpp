#include "speedinfo.h"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QThread>
#include <QtMath>
#include <QTimer>

#define PROC_PATH_UPTIME    "/proc/uptime"      // "系统启动" 和 "系统空闲" 的时间
#define PROC_PATH_CPU       "/proc/stat"        // "CPU" 使用率 的状态
#define PROC_PATH_MEM       "/proc/meminfo"     // "内存" 和 "交换空间" 的状态
#define PROC_PATH_NET       "/proc/net/dev"     // "网速" 下载和上传 的状态
#define PROC_PATH_DISK      "/proc/diskstats"   // "磁盘" 读取和写入 的状态

SpeedInfo::SpeedInfo(QObject *parent)
    :QObject(parent)
{
}

void SpeedInfo::init()
{
    m_timer = new QTimer(this);
}

double SpeedInfo::cpuRate(int decimalsNum, int ms)
{
    bool ok = false;
    double cpu = 0;
    long cpuAll = 0;
    long cpuFree = 0;
    long oldCpuAll = 0;
    long oldCpuFree = 0;

    // 实际第一次不准确,第二次开始才是准确的.
    while (true) {
        cpuRate(cpuAll, cpuFree);
        cpu = QString::number(static_cast<double>((cpuAll - oldCpuAll) - (cpuFree - oldCpuFree)) * 100.0 / (cpuAll - oldCpuAll), 'f', decimalsNum)
                .toDouble(&ok);

        qDebug()<<"-->CPU:"<<cpu<<"%   "<<cpuAll<<oldCpuAll<<cpuFree<<oldCpuFree<<(cpuAll - oldCpuAll) - (cpuFree - oldCpuFree)<<(cpuAll - oldCpuAll);

        oldCpuAll = cpuAll;
        oldCpuFree = cpuFree;

        QThread::msleep(ms);
    }

    return static_cast<double>((cpuAll - oldCpuAll - (cpuFree - oldCpuFree) ) * 1.0 / (cpuAll - oldCpuAll));
}

/*!
 * \brief SpeedInfo::memoryRate 获取内存和交换空间的使用率
 * \param memory 内存的使用率
 * \param swap 交换空间的使用率
 * \param decimalsNum 网速精确度:小数点后的个数
 * \param ms 每隔毫秒数,用来作为网速差的单位计算
 */
void SpeedInfo::memoryRate(double &memory, double &swap, int decimalsNum, int ms)
{
    long lMemory = 0;
    long lMemoryAll = 0;
    long lSwap = 0;
    long lSwapAll = 0;
    bool ok = false;

    while (true) {
        memoryRate(lMemory, lMemoryAll, lSwap, lSwapAll);
        memory = QString::number(static_cast<double>(lMemory * 100.0 / lMemoryAll), 'f', decimalsNum).toDouble(&ok);
        swap = QString::number(static_cast<double>(lSwap * 100.0 / lSwapAll), 'f', decimalsNum).toDouble(&ok);
        qDebug()<<QString("----->memory:%1 %,   swap:%2 %")
                  .arg(memory, 4, 'f', 2, QLatin1Char('0'))
                  .arg(swap, 4, 'f', 2, QLatin1Char('0'));
        QThread::msleep(ms);
    }
}

/*!
 * \brief SpeedInfo::cpuRate 获取本次 CPU 的状态
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
 * \brief SpeedInfo::memoryRate 内存 和 交换空间 的使用率
 * \param memory 内存使用占比
 * \param memoryAll 内存总量
 * \param swap 交换空间使用占比
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
 * \brief SpeedInfo::netRate 获取实时网速
 * \param[out] down 下载网速
 * \param[out] upload 上传网速
 * \param[out] downUnit 下载网速的单位
 * \param[out] uploadUnit 下载网速的单位
 * \param decimalsNum 网速精确度:小数点后的个数
 * \param ms 每隔毫秒数,用来作为网速差的单位计算
 * \param sensitive 默认输出速率单位的大小写模式
 * \return 获取是否成功
 */
void SpeedInfo::netRate(double &down, double &upload, QString &downUnit, QString &uploadUnit, int decimalsNum, int ms, Sensitive sensitive)
{
    long oldDown = 0;
    long oldUpload = 0;
    long tempDown = static_cast<double>(down);
    long tempUpload = static_cast<double>(upload);

    netRate(oldDown, oldUpload);
    while (true) {
        netRate(tempDown, tempUpload);
        RateUnit unit = RateUnit::RateByte;
        bool ok = false;
        down = QString::number(autoRateUnits(tempDown - oldDown, unit), 'f', decimalsNum).toDouble(&ok);
        downUnit = setRateUnitSensitive(unit, sensitive);
        oldDown = tempDown;

        unit = RateUnit::RateByte;
        upload = QString::number(autoRateUnits(tempUpload - oldUpload, unit), 'f', decimalsNum).toDouble(&ok);
        uploadUnit = setRateUnitSensitive(unit, sensitive);
        oldUpload = tempUpload;

        qDebug()<<"[up:]"<<upload<<uploadUnit<<"   [Down:]"<<down<<downUnit<<"  当前总的数据包 Down:"<<tempDown<<"   Up:"<<tempUpload;//<<"     ===>旧的数据:"<<oldDown<<"   "<<oldUpload;
        QThread::msleep(ms);
    }
}

/*!
 * \brief SpeedInfo::netRate 获取网络实时速率
 * \param[out] netUpload 网络上传速率
 * \param[out] netUpload 网络下载速率
 * \return 是否获取网络速率成功
 */
bool SpeedInfo::netRate(long &netDown, long &netUpload)
{
    if (netDown != 0 || netUpload != 0)
        netDown = netUpload = 0;

    QFile file(PROC_PATH_NET);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  // 在读取时，把行尾结束符修改为 '\n'； 在写入时，把行尾结束符修改为本地系统换行风格，比如Windows文本换行是 "\r\n"
        return false;

    long upload = 0;
    long down = 0;
    QTextStream stream(&file);
    QString line = stream.readLine();
    line  = stream.readLine();
    line  = stream.readLine();
    while (!line.isNull()) {
//        qDebug()<<"----->"<<line<<line.count();
        QStringList list = line.split(QRegExp("\\s{1,}"));   // 匹配任意 大于等于1个的 空白字符

        if (!list.isEmpty()) {
            upload = list.at(2).toLong();
            down = list.at(10).toLong();
        }

        netDown += upload;
        netUpload += down;
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
            return QString("Bit");
        case RateUnit::RateByte:
            return QString("Byte");
        case RateUnit::RateKb:
            return QString("Kb");
        case RateUnit::RateMb:
            return QString("Mb");
        case RateUnit::RateGb:
            return QString("Gb");
        case RateUnit::RateTb:
            return QString("Tb");
        default:
            qDebug()<<QString("Sensitive::Default,  RateUnit is RateUnknow.");
            return QString("");
        }
    }
    case Sensitive::Upper: {
        switch (unit) {
        case RateUnit::RateBit:
            return QString("Bit");
        case RateUnit::RateByte:
            return QString("BYTE");
        case RateUnit::RateKb:
            return QString("KB");
        case RateUnit::RateMb:
            return QString("MB");
        case RateUnit::RateGb:
            return QString("GB");
        case RateUnit::RateTb:
            return QString("TB");
        default:
            qDebug()<<QString("Sensitive::Upper,  RateUnit is RateUnknow.");
            return QString("");
        }
    }
    case Sensitive::Lower: {
        switch (unit) {
        case RateUnit::RateBit:
            return QString("bit");
        case RateUnit::RateByte:
            return QString("byte");
        case RateUnit::RateKb:
            return QString("kb");
        case RateUnit::RateMb:
            return QString("mb");
        case RateUnit::RateGb:
            return QString("gb");
        case RateUnit::RateTb:
            return QString("tb");
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


