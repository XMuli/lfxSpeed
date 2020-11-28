/*
 * Copyright (c) 2020 xmuli
 *
 * Author:  xmuli(偕臧) xmulitech@gmail.com
 * GitHub:  https://github.com/xmuli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * */

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
