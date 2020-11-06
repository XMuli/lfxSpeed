#ifndef SPEEDPLUGIN_H
#define SPEEDPLUGIN_H

#include <QObject>
#include <pluginsiteminterface.h>

class SpeedPlugin : public QObject, public PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)  // 声明实现了的接口
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "lfxSpeed.json")  // 插件元数据

public:
    explicit SpeedPlugin(QObject *parent = nullptr);

    virtual const QString pluginName() const override;
    virtual void init(PluginProxyInterface *proxyInter) override;
    virtual QWidget *itemWidget(const QString &itemKey) override;

private:
    PluginProxyInterface *m_proxyInter;
};

#endif // SPEEDPLUGIN_H
