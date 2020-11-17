#ifndef SPEEDPLUGIN_H
#define SPEEDPLUGIN_H

#include <QObject>
#include <pluginsiteminterface.h>

#include "speedwidget.h"

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

//    virtual QWidget *itemTipsWidget(const QString &itemKey) override;
//    virtual QWidget *itemPopupApplet(const QString &itemKey) override;
//    virtual void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;
//    virtual int itemSortKey(const QString &itemKey) override;
//    virtual void displayModeChanged(const Dock::DisplayMode displayMode) override;
//    virtual void positionChanged(const Dock::Position position) override;

private:
    PluginProxyInterface *m_proxyInter;
    SpeedWidget *m_speedWidget;
};

#endif // SPEEDPLUGIN_H
