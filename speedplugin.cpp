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

#include "aboutdialog.h"
#include "speedplugin.h"
#include "speedwidget.h"
#include "winmain.h"
#include "settingmodel.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <QDebug>

DWIDGET_USE_NAMESPACE

SpeedPlugin::SpeedPlugin(QObject *parent)
    : QObject(parent)
    , m_proxyInter(nullptr)
    , m_speedWidget(nullptr)
    , m_winMain(nullptr)
    , m_bMouseTip(true)
{
    connect(&m_timer, &QTimer::timeout, this, &SpeedPlugin::onUpdateTip);
    m_timer.setInterval(1000);
    m_timer.start();
}

const QString SpeedPlugin::pluginName() const
{
//    return QString("lfxSpeed");  datetime
    return "datetime";  // 假装我也叫这个，否则会被压缩，在 1.2.3 版本中才被修改
}

void SpeedPlugin::init(PluginProxyInterface *proxyInter)
{
    m_model = new SettingModel();

    m_proxyInter = proxyInter;
    m_speedWidget = new SpeedWidget(m_model);
    m_winMain = new WinMain(m_model);

    connect(m_winMain, &WinMain::sigMousTip, this, &SpeedPlugin::onMouseTip);
    // 如果插件没有被禁用, 则在初始化插件时才添加主控件到面板上
    if (!pluginIsDisable())
        m_proxyInter->itemAdded(this, pluginName());
}

QWidget *SpeedPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey)

    return m_speedWidget;
}

bool SpeedPlugin::pluginIsAllowDisable()
{
    // 告诉 dde-dock 本插件允许禁用
    return true;
}

bool SpeedPlugin::pluginIsDisable()
{
    // 第二个参数 “disabled” 表示存储这个值的键（所有配置都是以键值对的方式存储的）
    // 第三个参数表示默认值，即默认不禁用
    return m_proxyInter->getValue(this, "disabled", false).toBool();
}

void SpeedPlugin::pluginStateSwitched()
{
    // 将旧的 "禁用状态" 数值取反后,保存到 key-val 中
    const bool disableState = !pluginIsDisable();
    m_proxyInter->saveValue(this, "disabled", disableState);

    // 根据新的禁用状态值,处理主控的加载与卸载
    if (disableState)
        m_proxyInter->itemRemoved(this, pluginName());
    else
        m_proxyInter->itemAdded(this, pluginName());
}

const QString SpeedPlugin::pluginDisplayName() const
{
    return QString("lfxSpeed");
}

const QString SpeedPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    QList<QVariant> items;
    items.reserve(3);

    QMap<QString, QVariant> update;
    update["itemId"] = "update";
    update["itemText"] = "刷新";
    update["isActive"] = true;
    items.push_back(update);

    QMap<QString, QVariant> setting;
    setting["itemId"] = "setting";
    setting["itemText"] = "配置";
    setting["isActive"] = true;
    items.push_back(setting);

    QMap<QString, QVariant> about;
    about["itemId"] = "about";
    about["itemText"] = "关于";
    about["isActive"] = true;
    items.push_back(about);

    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // 返回 JSON 格式的菜单数据
    return QJsonDocument::fromVariant(menu).toJson();
}

void SpeedPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey)
    Q_UNUSED(checked)

    qApp->setAttribute(Qt::AA_UseHighDpiPixmaps);

    if (menuId == "update") {
        m_proxyInter->itemRemoved(this, pluginName());
        m_proxyInter->itemAdded(this, pluginName());
    } else if (menuId == "setting") {
        m_winMain->move((QApplication::desktop()->width() - m_winMain->width())/2,(QApplication::desktop()->height() - m_winMain->height())/2);
        m_winMain->show();
    } else if (menuId == "about") {
        AboutDialog * about = new AboutDialog();
        about->show();
    }
}

QWidget *SpeedPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey)
    if (m_bMouseTip)
        return &m_labTip;
    else
        return nullptr;
}

/*!
 * \brief SpeedPlugin::onUpdateTip 悬浮消息预览
 */
void SpeedPlugin::onUpdateTip()
{
    m_labTip.setText(m_speedWidget->networkInfo()
                     + m_speedWidget->m_runTime);
}

void SpeedPlugin::onMouseTip(int status)
{
    if (status == Qt::Checked)
        m_bMouseTip = true;
    else
        m_bMouseTip = false;
}
