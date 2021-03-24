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

#include "winmain.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <DLabel>
#include <DLineEdit>
#include <DCheckBox>
#include <DComboBox>
#include <QSpacerItem>
#include <DSpinBox>
#include <QWidget>
#include "speedplugin.h"
#include "settingmodel.h"

DWIDGET_USE_NAMESPACE

WinMain::WinMain(SettingModel *model, QWidget *parent)
    : DMainWindow(parent)
    , m_tab(new DTabWidget)
    , m_lineUpload(new DLineEdit)
    , m_lineDown(new DLineEdit)
    , m_lineCpu(new DLineEdit)
    , m_lineMemory(new DLineEdit)
    , m_checkUpAndDown(new DCheckBox)
    , m_checkMouseTips(new DCheckBox)
    , m_checkShowUp(new DCheckBox)
    , m_checkShowDown(new DCheckBox)
    , m_checkShowCPU(new DCheckBox)
    , m_checkShowMem(new DCheckBox)
    , m_spinDecimalsNum(new DSpinBox)
    , m_spinInterval(new DSpinBox)
    , m_comSensitive(new DComboBox)
    , m_model(model)
{
    init();

    connect(m_lineUpload, &DLineEdit::textChanged, this, &WinMain::sigLabUpload);
    connect(m_lineDown, &DLineEdit::textChanged, this, &WinMain::sigLabDown);
    connect(m_lineCpu, &DLineEdit::textChanged, this, &WinMain::sigLabCpu);
    connect(m_lineMemory, &DLineEdit::textChanged, this, &WinMain::sigLabMemory);
    void (DSpinBox:: *valueChanged)(int) = &DSpinBox::valueChanged;
    connect(m_spinDecimalsNum, valueChanged, this, &WinMain::sigDecimalsNum);
    connect(m_spinInterval, valueChanged, this, &WinMain::sigInterval);
    void (DComboBox:: *currentIndexChanged)(int index) = &DComboBox::currentIndexChanged;
    connect(m_comSensitive, currentIndexChanged, this, &WinMain::sigSensitive);

    connect(m_checkShowUp, &DCheckBox::stateChanged, this, &WinMain::sigShowUp);
    connect(m_checkShowDown, &DCheckBox::stateChanged, this, &WinMain::sigShowDown);
    connect(m_checkShowCPU, &DCheckBox::stateChanged, this, &WinMain::sigShowCPU);
    connect(m_checkShowMem, &DCheckBox::stateChanged, this, &WinMain::sigShowMem);
    connect(m_checkMouseTips, &DCheckBox::stateChanged, this, &WinMain::sigMousTip);

    connect(this, &WinMain::sigLabUpload, m_model, &SettingModel::sigUploadChange);
    connect(this, &WinMain::sigLabDown, m_model, &SettingModel::sigDownChange);
    connect(this, &WinMain::sigLabCpu, m_model, &SettingModel::sigCpuChange);
    connect(this, &WinMain::sigLabMemory, m_model, &SettingModel::sigMenoryChange);
    connect(this, &WinMain::sigDecimalsNum, m_model, &SettingModel::sigDecimalsNumChange);
    connect(this, &WinMain::sigInterval, m_model, &SettingModel::sigIntervalChange);
    connect(this, &WinMain::sigSensitive, m_model, &SettingModel::sigSensitiveChange);
    connect(this, &WinMain::sigShowUp, m_model, &SettingModel::sigShowUpChange);
    connect(this, &WinMain::sigShowDown, m_model, &SettingModel::sigShowDownChange);
    connect(this, &WinMain::sigShowCPU, m_model, &SettingModel::sigShowCPUChange);
    connect(this, &WinMain::sigShowMem, m_model, &SettingModel::sigShowMemChange);
}

void WinMain::init()
{
    // 任务栏窗口设置  --------------------------------------------
    QGroupBox* boxShowText = new QGroupBox(tr("显示文本:"));
    QGridLayout* gridShowText = new QGridLayout();
    gridShowText->addWidget(new DLabel(tr("上传:")), 0, 0);
    m_lineUpload->setText(tr("↑:"));
    gridShowText->addWidget(m_lineUpload, 0, 1);
    gridShowText->addWidget(new DLabel(tr("下载:")), 1, 0);
    m_lineDown->setText(tr("↓:"));
    gridShowText->addWidget(m_lineDown, 1, 1);
    gridShowText->addWidget(new DLabel(tr("CPU:")), 0, 2);
    m_lineCpu->setText(tr("CPU:"));
    gridShowText->addWidget(m_lineCpu, 0, 3);
    gridShowText->addWidget(new DLabel(tr("内存:")), 1, 2);
    m_lineMemory->setText(tr(" MEM:"));
    gridShowText->addWidget(m_lineMemory, 1, 3);

    QSpacerItem *vSpacer = new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Maximum);
    gridShowText->addItem(vSpacer, 2, 0);

    gridShowText->addWidget(new DLabel(tr("小数精确度:")), 3, 0);
    m_spinDecimalsNum->setMinimum(0);
    m_spinDecimalsNum->setValue(0);
    m_spinDecimalsNum->setSingleStep(1);
    gridShowText->addWidget(m_spinDecimalsNum, 3, 1);
    gridShowText->addWidget(new DLabel(tr("刷新时隔:")), 3, 2);
    m_spinInterval->setRange(1000, 2147483647);
    m_spinInterval->setValue(1000);
    m_spinInterval->setSingleStep(1000);
    m_spinInterval->setSuffix(tr("ms"));
    gridShowText->addWidget(m_spinInterval, 3, 3);
    gridShowText->addWidget(new DLabel(tr("单位模式:")), 4, 0);
    QStringList list;
    list<<"大小混写"<<"全部大写"<<"全部小写";
    m_comSensitive->addItems(list);
    gridShowText->addWidget(m_comSensitive, 4, 1);
    QSpacerItem *vSpacer2 = new QSpacerItem(1, 10, QSizePolicy::Maximum, QSizePolicy::Maximum);
    gridShowText->addItem(vSpacer2, 5, 0);

    QGridLayout* gridCheck = new QGridLayout();
    m_checkShowUp->setCheckState(Qt::Checked);
    m_checkShowUp->setText(tr("显示上传网速"));
    gridCheck->addWidget(m_checkShowUp, 0, 0);
    m_checkShowDown->setCheckState(Qt::Checked);
    m_checkShowDown->setText(tr("显示下载网速"));
    gridCheck->addWidget(m_checkShowDown, 0, 1);
    m_checkShowCPU->setCheckState(Qt::Checked);
    m_checkShowCPU->setText(tr("显示CPU"));
    gridCheck->addWidget(m_checkShowCPU, 0, 2);
    m_checkShowMem->setCheckState(Qt::Checked);
    m_checkShowMem->setText(tr("显示内存"));
    gridCheck->addWidget(m_checkShowMem, 0, 3);
    m_checkMouseTips->setCheckState(Qt::Checked);
    m_checkMouseTips->setText(tr("显示鼠标提示"));
    gridCheck->addWidget(m_checkMouseTips, 1, 0);
    m_checkUpAndDown->setCheckState(Qt::Unchecked);
    m_checkUpAndDown->setText(tr("上传下载互换"));

    QVBoxLayout* vLayout = new QVBoxLayout(boxShowText);
    vLayout->addLayout(gridShowText, 0);
    vLayout->addLayout(gridCheck, 1);

    DWidget *settingDock = new QWidget();
    QHBoxLayout* hLayoutDock = new QHBoxLayout(settingDock);
    hLayoutDock->addWidget(boxShowText);

    // 常规设置 --------------------------------------------
    m_tab->addTab(settingDock, tr("任务栏窗口设置"));
    setCentralWidget(m_tab);
}
