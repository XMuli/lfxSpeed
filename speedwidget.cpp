#include "speedwidget.h"

#include <QLabel>
#include <QDebug>

SpeedWidget::SpeedWidget(QWidget *parent)
    :QWidget(parent)
{
    QLabel* lable = new QLabel("plug-lfxSpeed", this);
    lable->resize(100, 40);
    qDebug()<<"----------SpeedWidget";
}
