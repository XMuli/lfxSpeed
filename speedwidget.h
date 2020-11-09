#ifndef SPEEDWIDGET_H
#define SPEEDWIDGET_H

#include <QWidget>

class QLabel;

class SpeedWidget : public QWidget
{
public:
    SpeedWidget(QWidget *parent = nullptr);

    void init();

    virtual QSize sizeHint() const override;
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QLabel *m_netUpload;
    QLabel *m_netDownload;
    QLabel *m_cpu;
    QLabel *m_memory;
    QLabel *m_diskRead;
    QLabel *m_diskWrite;
};

#endif // SPEEDWIDGET_H
