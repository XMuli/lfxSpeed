#ifndef WINMAIN_H
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

#define WINMAIN_H

#include <DMainWindow>
#include <DTabWidget>
#include <DCheckBox>
#include <DComboBox>

DWIDGET_BEGIN_NAMESPACE
class DLineEdit;
class DSpinBox;
//class DCheckBox; 奇怪, 怎么还不能声明了? 已经知道了
DWIDGET_END_NAMESPACE

class SettingModel;

DWIDGET_USE_NAMESPACE

class WinMain : public DMainWindow
{
    Q_OBJECT
public:
    WinMain(SettingModel *model, QWidget *parent = 0);

    void init();
    inline DLineEdit* getUpload(){return m_lineUpload;}

signals:
    void sigLabUpload(QString lineUpload);
    void sigLabDown(QString lineUpload);
    void sigLabCpu(QString lineUpload);
    void sigLabMemory(QString lineUpload);
    void sigDecimalsNum(const int num);
    void sigInterval(const int ms);
    void sigSensitive(const int index);

    void sigShowUp(int status);
    void sigShowDown(int status);
    void sigShowCPU(int status);
    void sigShowMem(int status);
    void sigMousTip(int status);
    void sigUpAndDown(int status);
    void sigOnlyOne(int status);

private:
    DTabWidget *m_tab;

    DLineEdit* m_lineUpload;
    DLineEdit* m_lineDown;
    DLineEdit* m_lineCpu;
    DLineEdit* m_lineMemory;
    DCheckBox* m_checkUpAndDown;
    DCheckBox* m_checkMouseTips;
    DCheckBox* m_checkShowUp;
    DCheckBox* m_checkShowDown;
    DCheckBox* m_checkShowCPU;
    DCheckBox* m_checkShowMem;
    DSpinBox*  m_spinDecimalsNum;
    DSpinBox*  m_spinInterval;
    DComboBox* m_comSensitive;

    SettingModel *m_model;
};

#endif // WINMAIN_H
