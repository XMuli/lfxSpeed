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

#include "speedwidget.h"

#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFont>

#include <DLabel>
#include <DGuiApplicationHelper>
#include "settingmodel.h"

DWIDGET_USE_NAMESPACE

SpeedWidget::SpeedWidget(SettingModel *model, QWidget *parent)
    : QWidget(parent)
    , m_labUpload(nullptr)
    , m_labDown(nullptr)
    , m_labCpu(nullptr)
    , m_labMemory(nullptr)
    , m_numUpload(nullptr)
    , m_numDown(nullptr)
    , m_numCpu(nullptr)
    , m_numMemory(nullptr)
    , m_timer(new QTimer(this))
    , m_DecimalsNum(0)
    , m_Sensitive(SpeedInfo::Default)
    , m_info(nullptr)
    , m_down(0)
    , m_upload(0)
    , m_cpuAll(0)
    , m_cpuFree(0)
    , m_model(model)
{
    init();

    connect(m_model, &SettingModel::sigUploadChange, this, &SpeedWidget::onSetLabUpload);
    connect(m_model, &SettingModel::sigDownChange, this, &SpeedWidget::onSetLabDown);
    connect(m_model, &SettingModel::sigCpuChange, this, &SpeedWidget::onSetLabCpu);
    connect(m_model, &SettingModel::sigMenoryChange, this, &SpeedWidget::onSetLabMemory);
    connect(m_model, &SettingModel::sigDecimalsNumChange, this, &SpeedWidget::onDecimalsNum);
    connect(m_model, &SettingModel::sigIntervalChange, this, &SpeedWidget::onUpdateInterval);
    connect(m_model, &SettingModel::sigSensitiveChange, this, &SpeedWidget::onSensitive);

    connect(m_model, &SettingModel::sigShowUpChange, this, &SpeedWidget::onShowUp);
    connect(m_model, &SettingModel::sigShowDownChange, this, &SpeedWidget::onShowDown);
    connect(m_model, &SettingModel::sigShowCPUChange, this, &SpeedWidget::onShowCPU);
    connect(m_model, &SettingModel::sigShowMemChange, this, &SpeedWidget::onShowMem);
}

/*!
 * \brief SpeedWidget::init 构建布局
 *  * \~chinese \htmlonly
 * <pre style="font-family: FreeMono, Consolas, Menlo, 'Noto Mono', 'Courier New', Courier, monospace;line-height: 100%;">
 * ==========================================================================
 * ||    上传标签    ||    网速 + 单位    ||    CPU标签    ||    CPU 使用率    ||
 * ==========================================================================
 * ||    下载标签    ||    网速 + 单位    ||    内存标签    ||    内存 使用率   ||
 * ==========================================================================
 * </pre>
 * \endhtmlonly
 */
void SpeedWidget::init()
{   
    m_labUpload = new DLabel(m_model->getStrUpload());
    m_labUpload->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_labDown = new DLabel(m_model->getStrDown());
    m_labDown->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_labCpu = new DLabel(" CPU:");
    m_labCpu->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_labMemory = new DLabel(" MEM:");
    m_labMemory->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_numUpload = new DLabel(tr("0 Kb/s"));
    m_numUpload->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_numDown = new DLabel(tr("0 Kb/s"));
    m_numDown->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_numCpu = new DLabel(tr("0 %"));
    m_numCpu->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_numMemory = new DLabel(tr("0 %"));
    m_numMemory->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    QFont font("Noto Sans Mono CJK SC", 9);
    QPalette palette;

    // 切换系统主题之后，需要重启 dde-dock 才能生效
    DGuiApplicationHelper *guiAppHelp = DGuiApplicationHelper::instance();
    if (guiAppHelp->themeType() == DGuiApplicationHelper::ColorType::DarkType)
        palette.setColor(QPalette::WindowText,Qt::white);
    else
        palette.setColor(QPalette::WindowText,Qt::black);

    m_labUpload->setFont(font);
    m_labDown->setFont(font);
    m_labCpu->setFont(font);
    m_labMemory->setFont(font);
    m_numUpload->setFont(font);
    m_numDown->setFont(font);
    m_numCpu->setFont(font);
    m_numMemory->setFont(font);

    m_labUpload->setPalette(palette);
    m_labDown->setPalette(palette);
    m_labCpu->setPalette(palette);
    m_labMemory->setPalette(palette);
    m_numUpload->setPalette(palette);
    m_numDown->setPalette(palette);
    m_numCpu->setPalette(palette);
    m_numMemory->setPalette(palette);

    QVBoxLayout *VLayout1 = new QVBoxLayout();
    VLayout1->setContentsMargins(0, 0, 0, 0);
    VLayout1->setSpacing(0);
    VLayout1->addWidget(m_labUpload);
    VLayout1->addWidget(m_labDown);
    QVBoxLayout *VLayout2 = new QVBoxLayout();
    VLayout2->setContentsMargins(0, 0, 0, 0);
    VLayout2->setSpacing(0);
    VLayout2->addWidget(m_numUpload);
    VLayout2->addWidget(m_numDown);
    QVBoxLayout *VLayout3 = new QVBoxLayout();
    VLayout3->setContentsMargins(0, 0, 0, 0);
    VLayout3->setSpacing(0);
    VLayout3->addWidget(m_labCpu);
    VLayout3->addWidget(m_labMemory);
    QVBoxLayout *VLayout4 = new QVBoxLayout();
    VLayout4->setContentsMargins(0, 0, 0, 0);
    VLayout4->setSpacing(0);
    VLayout4->addWidget(m_numCpu);
    VLayout4->addWidget(m_numMemory);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addLayout(VLayout1);
    hLayout->addLayout(VLayout2);
    hLayout->addLayout(VLayout3);
    hLayout->addLayout(VLayout4);
    setLayout(hLayout);

    layout = new QGridLayout();
    layout->setContentsMargins(0, 0, 0, 0);

    m_info = new SpeedInfo(this);
    m_info->netRate(m_down, m_upload);
    m_info->cpuRate(m_cpuAll, m_cpuFree);

    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onUpdateNet);
    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onUpdateCpu);
    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onUpdateMemory);
    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onRunTime);
    m_timer->setInterval(1000);
    m_timer->start();
}

void SpeedWidget::onUpdateNet()
{
    long down = 0;
    long upload = 0;
    double downRate = 0;
    double uploadRate = 0;
    SpeedInfo::RateUnit unit = SpeedInfo::RateByte;

    m_info->netRate(down, upload);
    downRate = m_info->autoRateUnits((down - m_down) / (m_timer->interval() / 1000), unit);
    QString downUnit = m_info->setRateUnitSensitive(unit, m_Sensitive);
    unit = SpeedInfo::RateByte;
    uploadRate = m_info->autoRateUnits((upload - m_upload) / (m_timer->interval() / 1000), unit);
    QString uploadUnit = m_info->setRateUnitSensitive(unit, m_Sensitive);
    m_numDown->setText(QString("%1").arg(downRate, 3, 'f', m_DecimalsNum, QLatin1Char(' ')) + downUnit);
    m_numUpload->setText(QString("%1").arg(uploadRate, 3, 'f', m_DecimalsNum, QLatin1Char(' ')) + uploadUnit);

    m_down = down;
    m_upload = upload;
}

void SpeedWidget::onUpdateCpu()
{
    long cpuAll = 0;
    long cpuFree = 0;
    m_info->cpuRate(cpuAll, cpuFree);
    m_numCpu->setText(QString("%1%").arg((((cpuAll - m_cpuAll) - (cpuFree - m_cpuFree)) * 100.0 / (cpuAll - m_cpuAll)), 2, 'f', m_DecimalsNum, QLatin1Char(' ')));

    m_cpuAll = cpuAll;
    m_cpuFree = cpuFree;
}

void SpeedWidget::onUpdateMemory()
{
    long memory = 0;
    long memoryAll = 0;
    long swap = 0;
    long swapAll = 0;

    m_info->memoryRate(memory, memoryAll, swap, swapAll);
    m_numMemory->setText(QString("%1%").arg(memory * 100.0 / memoryAll, 2, 'f', m_DecimalsNum, QLatin1Char(' ')));
}

void SpeedWidget::onSetLabUpload(const QString upload)
{
    m_labUpload->setText(upload);
}

void SpeedWidget::onSetLabDown(const QString down)
{
    m_labDown->setText(down);
}

void SpeedWidget::onSetLabCpu(const QString cpu)
{
    m_labCpu->setText(cpu);
}

void SpeedWidget::onSetLabMemory(const QString memory)
{
    m_labMemory->setText(memory);
}

void SpeedWidget::onDecimalsNum(const int num)
{
    m_DecimalsNum = num;
}

void SpeedWidget::onUpdateInterval(const int ms)
{
    m_timer->setInterval(ms);
}

void SpeedWidget::onSensitive(const int index)
{
    if (index == 0) {
        m_Sensitive = SpeedInfo::Default;
    } else if (index == 1) {
        m_Sensitive = SpeedInfo::Upper;
    } else if (index == 2) {
        m_Sensitive = SpeedInfo::Lower;
    }
}

void SpeedWidget::onShowUp(int status)
{
    if (checkToBool(status)) {
        m_labUpload->show();
        m_numUpload->show();
    } else {
        m_labUpload->hide();
        m_numUpload->hide();
    }

//    updateGeometry();
//    update();
//    adjustSize();
}

void SpeedWidget::onShowDown(int status)
{
    if (checkToBool(status)) {
        m_labDown->show();
        m_numDown->show();
    } else {
        m_labDown->hide();
        m_numDown->hide();
    }
}

void SpeedWidget::onShowCPU(int status)
{
    if (checkToBool(status)) {
        m_labCpu->show();
        m_numCpu->show();
    } else {
        m_labCpu->hide();
        m_numCpu->hide();
    }
}

void SpeedWidget::onShowMem(int status)
{
    if (checkToBool(status)) {
    } else {
    }


    if (checkToBool(status)) {
        m_labMemory->show();
        m_numMemory->show();
    } else {
        m_labMemory->hide();
        m_numMemory->hide();
    }
}

QString SpeedWidget::onRunTime()
{
    double run = 0;
    double idel = 0;
    m_info->uptime(run, idel);
    m_runTime = m_info->autoTimeUnits(run);

    return m_runTime;
}

bool SpeedWidget::checkToBool(int status)
{
    if (status == Qt::Checked)
        return true;
    else
        return false;
}
