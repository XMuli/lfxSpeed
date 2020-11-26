#include "settingmodel.h"

#include <DLabel>


DWIDGET_USE_NAMESPACE

SettingModel::SettingModel(QObject *parent)
    : QObject(parent)
    , m_strUpload("↑:")
    , m_strDown("↓:")
    , m_strCpu("CPU:")
    , m_strMemory("内存:")
    , m_bUpAndDown(true)
    , m_bMouseTips(true)
    , m_nDecimalsNum(2)
    , m_nInterval(1000)
{
}

void SettingModel::init()
{

}

const QString SettingModel::getStrUpload()
{
    return m_strUpload;
}

const QString SettingModel::getStrDown()
{
    return m_strDown;
}

const QString SettingModel::getStrCpu()
{
    return m_strCpu;
}

const QString SettingModel::getStrMemory()
{
    return m_strMemory;
}

const bool SettingModel::getUpAndDown()
{
    return m_bUpAndDown;
}

const bool SettingModel::getMouseTips()
{
    return m_bMouseTips;
}

const int SettingModel::getDecimalsNum()
{
    return m_nDecimalsNum;
}

const int SettingModel::getInterval()
{
    return m_nInterval;
}
