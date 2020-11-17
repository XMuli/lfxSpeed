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
//    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void onUpdateNet();

private:
    DLabel *m_netUpload;
    DLabel *m_netDown;
    DLabel *m_cpu;
    DLabel *m_memory;
    DLabel *m_diskRead;
    DLabel *m_diskWrite;
    QTimer *m_timer;
    SpeedInfo *m_speedInfo;

    long m_down;
    long m_upload;


};

#endif // SPEEDWIDGET_H
