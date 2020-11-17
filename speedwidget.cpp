#include "speedwidget.h"

#include <QDebug>
#include <QGridLayout>
#include <QPainter>
#include <QTimer>
#include <QDateTime>

#include <DLabel>
#include "speedinfo.h"

DWIDGET_USE_NAMESPACE

SpeedWidget::SpeedWidget(QWidget *parent)
    : QWidget(parent)
    , m_netUpload(nullptr)
    , m_netDown(nullptr)
    , m_cpu(nullptr)
    , m_memory(nullptr)
    , m_diskRead(nullptr)
    , m_diskWrite(nullptr)
    , m_timer(nullptr)
    , m_info(nullptr)
    , m_down(0)
    , m_upload(0)
{
    init();
}

void SpeedWidget::init()
{
    m_netUpload = new DLabel(tr("↑: 0 kb/s"));
    m_netDown = new DLabel(tr("↓: 0 kb/s"));
//    m_cpu = new DLabel(tr("CPU: 0 %"));
//    m_memory = new DLabel(tr("MEM: 0 %"));
//    m_diskRead = new DLabel(tr("↗: 0 kb/s"));
//    m_diskWrite = new DLabel(tr("↙: 0 kb/s"));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_netUpload, 0, 0);
    layout->addWidget(m_netDown, 1, 0);
//    layout->addWidget(m_cpu, 0, 1);
//    layout->addWidget(m_memory, 1, 1);
//    layout->addWidget(m_diskRead, 0, 2);
//    layout->addWidget(m_diskWrite, 1, 2);

    m_info = new SpeedInfo(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onUpdateNet);
    m_timer->start();
}

//void SpeedWidget::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//    QPainter pa(this);
//    pa.setPen(QPen(Qt::red));
//    pa.drawRect(rect());
//    qDebug()<<"------------>"<<rect();
//}

void SpeedWidget::onUpdateNet()
{
    long down = 0;
    long upload = 0;
    double downRate = 0;
    double uploadRate = 0;
    SpeedInfo::RateUnit unit = SpeedInfo::RateByte;

    m_info->netRate(down, upload);
    downRate = m_info->autoRateUnits(down - m_down, unit);
    QString downUnit = m_info->setRateUnitSensitive(unit, SpeedInfo::Default);
    unit = SpeedInfo::RateByte;
    uploadRate = m_info->autoRateUnits(upload - m_upload, unit);
    QString uploadUnit = m_info->setRateUnitSensitive(unit, SpeedInfo::Default);

    m_down = down;
    m_upload = upload;

    m_netDown->setText(tr("↓:") + QString("%1").arg(downRate, 0, 'f', 2, QLatin1Char(' ')) + downUnit);
    m_netUpload->setText(tr("↑:") + QString("%1").arg(uploadRate, 0, 'f', 2, QLatin1Char(' ')) + uploadUnit);
}
