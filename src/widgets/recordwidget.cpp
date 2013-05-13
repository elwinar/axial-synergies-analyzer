#include "recordwidget.h"

#include <QDebug>
#include <QPair>
#include <QSettings>
#include <QString>

#include "utils/record.h"
#include "widgets/motiondetectorwidget.h"

RecordWidget::RecordWidget(QWidget *parent) : QTabWidget(parent)
{
    _settings = 0;
    _record = 0;
    initializeMotionDetectorWidget();
}

void RecordWidget::initializeMotionDetectorWidget()
{
    _motionDetectorWidget = new MotionDetectorWidget();
    addTab(_motionDetectorWidget, tr("Motion Detection"));
}

void RecordWidget::setRecord(Record * value)
{
    _record = value;
    _motionDetectorWidget->setRecord(_record);
}

void RecordWidget::setSettings(QSettings * value)
{
    qDebug() << "[recordwidget] got settings (" << value << ")";
    _settings = value;
    if(_settings != 0)
    {
        QString fixedProximal = _settings->value("motiondetector/fixed_proximal", QString()).toString();
        QString fixedDistal = _settings->value("motiondetector/fixed_distal", QString()).toString();
        QString mobileProximal = _settings->value("motiondetector/mobile_proximal", QString()).toString();
        QString mobileDistal = _settings->value("motiondetector/mobile_distal", QString()).toString();
        _motionDetectorWidget->setDefaultAngle(QPair<QString, QString>(fixedProximal, fixedDistal), QPair<QString, QString>(mobileProximal, mobileDistal));
    }
}
