#include "speedinfo.h"

#include <QFile>
#include <QString>

#define PROC_PATH_UPTIME    "/proc/uptime"      // "系统启动" 和 "系统空闲" 的时间
#define PROC_PATH_CPU       "/proc/stat"        // "CPU" 使用率 的状态
#define PROC_PATH_MEM       "/proc/meminfo"     // "内存" 和 "交换空间" 的状态
#define PROC_PATH_NET       "/proc/net/dev"     // "网速" 下载和上传 的状态
#define PROC_PATH_DISK      "/proc/diskstats"   // "磁盘" 读取和写入 的状态

SpeedInfo::SpeedInfo()
{

}

/*!
 * \brief SpeedInfo::netSpeed 获取网络实时速率
 * \param[out] netUpdate 网络上传速率
 * \param[out] netDown 网络下载速率
 * \return 是否获取网络速率成功
 */
bool SpeedInfo::netSpeed(long &netUpdate, long &netDown)
{
    if (netUpdate != 0 || netDown != 0)
        netUpdate = netDown = 0;

    QFile file(PROC_PATH_NET);
    file.open(QIODevice::ReadOnly);
    QByteArray line = file.readLine();
    while (!file.atEnd()) {
        line = file.readLine();


    }


    file.close();

}
