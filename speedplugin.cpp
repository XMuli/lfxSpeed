#include "speedplugin.h"

SpeedPlugin::SpeedPlugin(QObject *parent)
    :QObject(parent)
{
    qDebug()<<"============lfxSpeed============";
}

const QString SpeedPlugin::pluginName() const
{
    return "lfxSpeed";
}

void SpeedPlugin::init(PluginProxyInterface *proxyInter)
{
    m_proxyInter = proxyInter;
}

QWidget *SpeedPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey)

    // 这里暂时返回空指针，这意味着插件会被 dde-dock 加载
    // 但是不会有任何东西被添加到 dde-dock 上
    return nullptr;
}
