#ifndef SPEEDINFO_H
#define SPEEDINFO_H

#define PROC_PATH_UPTIME    "/proc/uptime"      // "系统启动" 和 "系统空闲" 的时间
#define PROC_PATH_CPU       "/proc/stat"        // "CPU" 使用率 的状态
#define PROC_PATH_MEM       "/proc/meminfo"     // "内存" 和 "交换空间" 的状态
#define PROC_PATH_NET       "/proc/net/dev"     // "网速" 下载和上传 的状态
#define PROC_PATH_DISK      "/proc/diskstats"   // "磁盘" 读取和写入 的状态

class QString;

class SpeedInfo
{
public:
    SpeedInfo();

    bool systemTime(QString &startup, QString &free);
    bool cpuSpeed(long &cpu);
    bool memorySpeed(long &memory, long &swap);
    bool diskSpeed(long &read, long &write);
    bool netSpeed(long &netUpdate, long &netDown);
};

#endif // SPEEDINFO_H
