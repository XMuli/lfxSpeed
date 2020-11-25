#include "winmain.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <DLabel>
#include <DLineEdit>
#include <DCheckBox>
#include <DComboBox>
#include <QSpacerItem>
#include <DSpinBox>
#include <QWidget>

DWIDGET_USE_NAMESPACE

WinMain::WinMain(QWidget *parent)
    : DMainWindow(parent)
    , m_tab(new DTabWidget)
    , m_lineUpload(new DLineEdit)
    , m_lineDown(new DLineEdit)
    , m_lineCpu(new DLineEdit)
    , m_lineMemory(new DLineEdit)
    , m_checkUpAndDown(new DCheckBox)
    , m_checkMouseTips(new DCheckBox)
    , m_spinDecimalsNum(new DSpinBox)
    , m_spinInterval(new DSpinBox)
    , m_comSensitive(new DComboBox)
{
    init();
}

void WinMain::init()
{

    // 主窗口设置  --------------------------------------------
    DWidget *settingMain = new QWidget();

    // 任务栏窗口设置  --------------------------------------------
    QGroupBox* boxShowText = new QGroupBox(tr("显示文本:"));
    QGridLayout* gridShowText = new QGridLayout();
    gridShowText->addWidget(new DLabel(tr("上传:")), 0, 0);
    m_lineUpload->setText(tr("↑:"));
    gridShowText->addWidget(m_lineUpload, 0, 1);
    gridShowText->addWidget(new DLabel(tr("下载:")), 1, 0);
    m_lineDown->setText(tr("↓:"));
    gridShowText->addWidget(m_lineDown, 1, 1);
    gridShowText->addWidget(new DLabel(tr("CPU:")), 0, 2);
    m_lineCpu->setText(tr("CPU:"));
    gridShowText->addWidget(m_lineCpu, 0, 3);
    gridShowText->addWidget(new DLabel(tr("内存:")), 1, 2);
    m_lineMemory->setText(tr("MEM:"));
    gridShowText->addWidget(m_lineMemory, 1, 3);

    QSpacerItem *vSpacer = new QSpacerItem(1, 1, QSizePolicy::Maximum, QSizePolicy::Maximum);
    gridShowText->addItem(vSpacer, 2, 0);

    gridShowText->addWidget(new DLabel(tr("小数精确度:")), 3, 0);
    m_spinDecimalsNum->setMinimum(0);
    m_spinDecimalsNum->setValue(2);
    m_spinDecimalsNum->setSingleStep(1);
    gridShowText->addWidget(m_spinDecimalsNum, 3, 1);
    gridShowText->addWidget(new DLabel(tr("刷新时隔:")), 3, 2);
    m_spinInterval->setRange(0, 2147483647);
    m_spinInterval->setValue(1000);
    m_spinInterval->setSingleStep(1000);
    m_spinInterval->setSuffix(tr("ms"));
    gridShowText->addWidget(m_spinInterval, 3, 3);
    gridShowText->addWidget(new DLabel(tr("单位模式:")), 4, 0);
    QStringList list;
    list<<"大小混写"<<"全部大写"<<"全部小写";
    m_comSensitive->addItems(list);
    gridShowText->addWidget(m_comSensitive, 4, 1);
    QSpacerItem *vSpacer2 = new QSpacerItem(1, 10, QSizePolicy::Maximum, QSizePolicy::Maximum);
    gridShowText->addItem(vSpacer2, 5, 0);

    QGridLayout* gridCheck = new QGridLayout();
    m_checkUpAndDown->setCheckState(Qt::Checked);
    m_checkUpAndDown->setText(tr("交换上传和下载的位置"));
    gridCheck->addWidget(m_checkUpAndDown, 2, 0);
    m_checkMouseTips->setCheckState(Qt::Checked);
    m_checkMouseTips->setText(tr("显示鼠标提示"));
    gridCheck->addWidget(m_checkMouseTips, 2, 1);

    QVBoxLayout* vLayout = new QVBoxLayout(boxShowText);
    vLayout->addLayout(gridShowText, 0);
    vLayout->addLayout(gridCheck, 1);

    DWidget *settingDock = new QWidget();
    QHBoxLayout* hLayoutDock = new QHBoxLayout(settingDock);
    hLayoutDock->addWidget(boxShowText);

    // 常规设置 --------------------------------------------
    DWidget *settingOther = new QWidget();

//    m_tab->addTab(settingMain, tr("主窗口设置"));
    m_tab->addTab(settingDock, tr("任务栏窗口设置"));
//    m_tab->addTab(settingOther, tr("常规设置"));
    setCentralWidget(m_tab);
}
