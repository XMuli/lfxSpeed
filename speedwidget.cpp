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
    , m_labUpload(nullptr)
    , m_labDown(nullptr)
    , m_labCpu(nullptr)
    , m_labMemory(nullptr)
    , m_numUpload(nullptr)
    , m_numDown(nullptr)
    , m_numCpu(nullptr)
    , m_numMemory(nullptr)
    , m_diskRead(nullptr)
    , m_diskWrite(nullptr)
    , m_timer(nullptr)
    , m_info(nullptr)
    , m_down(0)
    , m_upload(0)
    , m_cpuAll(0)
    , m_cpuFree(0)
{
    init();
}

/*!
 * \brief SpeedWidget::init 构建布局
 *  * \~chinese \htmlonly
 * <pre style="font-family: FreeMono, Consolas, Menlo, 'Noto Mono', 'Courier New', Courier, monospace;line-height: 100%;">
 * ==========================================================================
 * ||    上传标签    ||    网速 + 单位    ||    CPU标签    ||    CPU 使用率    ||
 * ==========================================================================
 * ||    下载标签    ||    网速 + 单位    ||    内存标签    ||    内存 使用率   ||
 * ==========================================================================
 * </pre>
 * \endhtmlonly
 */
void SpeedWidget::init()
{
    m_numUpload = new DLabel(tr("0 Kb/s"));
    m_numUpload->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_numDown = new DLabel(tr("0 Kb/s"));
    m_numDown->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_numCpu = new DLabel(tr("0 %"));
    m_numCpu->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_numMemory = new DLabel(tr("0 %"));
    m_numMemory->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    m_diskRead = new DLabel(tr("↗: 0 kb/s"));
//    m_diskWrite = new DLabel(tr("↙: 0 kb/s"));

    QGridLayout *layout = new QGridLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_labUpload = new DLabel(tr("↑: "));
    m_labUpload->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_labDown = new DLabel(tr("↓: "));
    m_labDown->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_labCpu = new DLabel(tr(" CPU: "));
    m_labCpu->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_labMemory = new DLabel(tr(" MEM: "));
    m_labMemory->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(m_labUpload, 0, 0);
    layout->addWidget(m_numUpload, 0, 1);
    layout->addWidget(m_labDown, 1, 0);
    layout->addWidget(m_numDown, 1, 1);
    layout->addWidget(m_labCpu, 0, 2);
    layout->addWidget(m_numCpu, 0, 3);
    layout->addWidget(m_labMemory, 1, 2);
    layout->addWidget(m_numMemory, 1, 3);
//    layout->addWidget(m_diskRead, 0, 2);
//    layout->addWidget(m_diskWrite, 1, 2);

    m_info = new SpeedInfo(this);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onUpdateNet);
    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onUpdateCpu);
    connect(m_timer, &QTimer::timeout, this, &SpeedWidget::onUpdateMemory);
    m_timer->start();
}

//void SpeedWidget::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//    QPainter pa(this);
//    pa.setPen(QPen(Qt::red));
//    pa.drawRect(rect());
//    qDebug()<<"-----------#######->"<<rect();
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
    m_numDown->setText(QString("%1").arg(downRate, 0, 'f', 2, QLatin1Char(' ')) + downUnit);
    m_numUpload->setText(QString("%1").arg(uploadRate, 0, 'f', 2, QLatin1Char(' ')) + uploadUnit);

    m_down = down;
    m_upload = upload;
}

void SpeedWidget::onUpdateCpu()
{
    long cpuAll = 0;
    long cpuFree = 0;
    m_info->cpuRate(cpuAll, cpuFree);
    m_numCpu->setText(QString("%1%").arg((((cpuAll - m_cpuAll) - (cpuFree - m_cpuFree)) * 100.0 / (cpuAll - m_cpuAll)), 0, 'f', 2, QLatin1Char(' ')));

    m_cpuAll = cpuAll;
    m_cpuFree = cpuFree;
}

void SpeedWidget::onUpdateMemory()
{
    long memory = 0;
    long memoryAll = 0;
    long swap = 0;
    long swapAll = 0;

    m_info->memoryRate(memory, memoryAll, swap, swapAll);
    m_numMemory->setText(QString("%1%").arg(memory * 100.0 / memoryAll, 0, 'f', 2, QLatin1Char(' ')));
}
