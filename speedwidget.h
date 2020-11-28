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

#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>
#include <dtkwidget_global.h>
#include "speedinfo.h"

DWIDGET_BEGIN_NAMESPACE
class DLabel;
DWIDGET_END_NAMESPACE

class QTimer;
class QGridLayout;
class SettingModel;

DWIDGET_USE_NAMESPACE

class SpeedWidget : public QWidget
{
    Q_OBJECT
public:
    SpeedWidget(SettingModel *model, QWidget *parent = nullptr);

    void init();
//    virtual QSize sizeHint() const override;
//    void resizeEvent(QResizeEvent *event);
//    virtual void paintEvent(QPaintEvent *event) override;
    QString m_runTime;

public slots:
    void onUpdateNet();
    void onUpdateCpu();
    void onUpdateMemory();
    void onSetLabUpload(const QString upload);
    void onSetLabDown(const QString down);
    void onSetLabCpu(const QString cpu);
    void onSetLabMemory(const QString memory);
    void onUpAndDown(Qt::CheckState check);
    void onDecimalsNum(const int num);
    void onUpdateInterval(const int ms);
    void onSensitive(const int index);

    void onShowUp(int status);
    void onShowDown(int status);
    void onShowCPU(int status);
    void onShowMem(int status);
    QString onRunTime();

private:
    bool checkToBool(int status);

private:
    DLabel *m_labUpload;
    DLabel *m_labDown;
    DLabel *m_labCpu;
    DLabel *m_labMemory;

    DLabel *m_numUpload;
    DLabel *m_numDown;
    DLabel *m_numCpu;
    DLabel *m_numMemory;
    DLabel *m_diskRead;
    DLabel *m_diskWrite;
    QTimer *m_timer;
    int m_DecimalsNum;
    SpeedInfo::Sensitive m_Sensitive;
    SpeedInfo *m_info;

    long m_down;
    long m_upload;
    long m_cpuAll;
    long m_cpuFree;

    QGridLayout *layout;
    SettingModel *m_model;
};

#endif // SPEEDWIDGET_H
