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
    m_speedWidget = new SpeedWidget();

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
    m_proxyInter->getValue(this, "disabled", disableState);

    // 根据新的禁用状态值,处理主控的加载与卸载
    if (disableState)
        m_proxyInter->itemAdded(this, pluginName());
    else
        m_proxyInter->itemRemoved(this, pluginName());
}

const QString SpeedPlugin::pluginDisplayName() const
{
    return tr("lfxSpeed");
}

//QWidget *SpeedPlugin::itemTipsWidget(const QString &itemKey)
//{
//}

//QWidget *SpeedPlugin::itemPopupApplet(const QString &itemKey)
//{

//}

//void SpeedPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
//{

//}

//int SpeedPlugin::itemSortKey(const QString &itemKey)
//{

//}

//void SpeedPlugin::displayModeChanged(const Dock::DisplayMode displayMode)
//{

//}

//void SpeedPlugin::positionChanged(const Dock::Position position)
//{

//}
