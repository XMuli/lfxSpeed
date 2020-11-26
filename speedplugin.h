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

#ifndef SPEEDPLUGIN_H
#define SPEEDPLUGIN_H

#include <QObject>
#include <pluginsiteminterface.h>
#include <dtkwidget_global.h>
#include "dlabel.h"

class QTimer;
class SpeedInfo;
class WinMain;
class SpeedWidget;
class SettingModel;

DWIDGET_USE_NAMESPACE

class SpeedPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)  // 声明实现了的接口
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "lfxSpeed.json")  // 插件元数据

public:
    explicit SpeedPlugin(QObject *parent = nullptr);

    // 插件必须重写函数
    virtual const QString pluginName() const override;
    virtual void init(PluginProxyInterface *proxyInter) override;
    virtual QWidget *itemWidget(const QString &itemKey) override;

    // 插件禁用和启用相关的接口
    virtual bool pluginIsAllowDisable() override;
    virtual bool pluginIsDisable() override;
    virtual void pluginStateSwitched() override;

    virtual const QString pluginDisplayName() const override;
    virtual const QString itemContextMenu(const QString &itemKey) override;
    virtual void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;
    virtual QWidget *itemTipsWidget(const QString &itemKey) override;

signals:
    void labUpload(const QString &labUpload);

public slots:
    void onUpdateTip();

private:
    PluginProxyInterface *m_proxyInter;
    SpeedWidget *m_speedWidget;
    WinMain *m_winMain;
    SettingModel *m_model;

    DLabel m_labTip;
    QTimer m_timer;
};

#endif // SPEEDPLUGIN_H
