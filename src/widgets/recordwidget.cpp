#include "recordwidget.h"

#include <QDebug>

#include "utils/record.h"
#include "widgets/motiondetectorwidget.h"

RecordWidget::RecordWidget(Record * record, QWidget *parent) : QTabWidget(parent)
{
    setRecord(record);
    initializeMotionDetectorWidget();
}

void RecordWidget::initializeMotionDetectorWidget()
{
    _motionDetectorWidget = new MotionDetectorWidget();
    addTab(_motionDetectorWidget, tr("Motion Detection"));
    QObject::connect(this, SIGNAL(recordChanged(Record *)), _motionDetectorWidget, SLOT(setRecord(Record *)));
}

void RecordWidget::setRecord(Record * record)
{
    _record = record;
    emit recordChanged(record);
}
