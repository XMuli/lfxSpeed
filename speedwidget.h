#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>

#include <dtkwidget_global.h>

DWIDGET_BEGIN_NAMESPACE
class DLabel;
DWIDGET_END_NAMESPACE

class QTimer;
class SpeedInfo;

DWIDGET_USE_NAMESPACE

class SpeedWidget : public QWidget
{
public:
    SpeedWidget(QWidget *parent = nullptr);

    void init();
//    virtual QSize sizeHint() const override;
//    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void onUpdateNet();
    void onUpdateCpu();
    void onUpdateMemory();

private:
    DLabel *m_labUpload;
    DLabel *m_labDown;
    DLabel *m_labCpu;
    DLabel *m_labMemory;

    DLabel *m_numUpload;
    DLabel *m_numDown;
    DLabel *m_numCpu;
    DLabel *m_numMemory;
    DLabel *m_diskRead;
    DLabel *m_diskWrite;
    QTimer *m_timer;
    SpeedInfo *m_info;

    long m_down;
    long m_upload;
    long m_cpuAll;
    long m_cpuFree;

};

#endif // SPEEDWIDGET_H
