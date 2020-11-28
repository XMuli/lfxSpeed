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

#ifndef SETTINGMODEL_H
#define SETTINGMODEL_H

#include <QObject>
#include <dtkwidget_global.h>
#include "speedinfo.h"
#include "speedwidget.h"
#include "winmain.h"

DWIDGET_BEGIN_NAMESPACE
class DLabel;
DWIDGET_END_NAMESPACE


DWIDGET_USE_NAMESPACE

class SettingModel : public QObject
{
    Q_OBJECT

public:
    SettingModel(QObject *parent = 0);

    void init();

public:
    const QString getStrUpload();
    const QString getStrDown();
    const QString getStrCpu();
    const QString getStrMemory();
    const bool getUpAndDown();
    const bool getMouseTips();
    const int getDecimalsNum();
    const int getInterval();

signals:
    void sigUploadChange(QString upload);
    void sigDownChange(QString upload);
    void sigCpuChange(QString upload);
    void sigMenoryChange(QString upload);
//    void sigUpAndDownChange(Qt::CheckState check);
    void sigDecimalsNumChange(const int num);
    void sigIntervalChange(const int ms);
    void sigSensitiveChange(const int index);

    void sigShowUpChange(int status);
    void sigShowDownChange(int status);
    void sigShowCPUChange(int status);
    void sigShowMemChange(int status);

private:
    QString m_strUpload;
    QString m_strDown;
    QString m_strCpu;
    QString m_strMemory;

    bool m_bUpAndDown;
    bool m_bMouseTips;

    int m_nDecimalsNum;
    int m_nInterval;
};

#endif // SETTINGMODEL_H
