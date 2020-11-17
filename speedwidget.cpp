#include "speedwidget.h"

#include <QLabel>
#include <QDebug>
#include <QGridLayout>
#include <QPainter>

SpeedWidget::SpeedWidget(QWidget *parent)
    :QWidget(parent)
{
    init();
}

void SpeedWidget::init()
{
    m_netUpload = new QLabel(tr("↑: 0 kb/s"), nullptr);
    m_netDownload = new QLabel(tr("↓: 0 kb/s"));
    m_cpu = new QLabel(tr("CPU: 0 %"));
    m_memory = new QLabel(tr("MEM: 0 %"));
    m_diskRead = new QLabel(tr("↗: 0 kb/s"));
    m_diskWrite = new QLabel(tr("↙: 0 kb/s"));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_netUpload, 0, 0);
    layout->addWidget(m_netDownload, 1, 0);
    layout->addWidget(m_cpu, 0, 1);
    layout->addWidget(m_memory, 1, 1);
    layout->addWidget(m_diskRead, 0, 2);
    layout->addWidget(m_diskWrite, 1, 2);

    qDebug()<<"----------SpeedWidget";
}

void SpeedWidget::paintEvent(QPaintEvent *event)
{
    QPainter pa(this);
    pa.fillRect(rect(), Qt::red);
}
