#include "recordwidget.h"

#include "widgets/motiondetectorwidget.h"

RecordWidget::RecordWidget(QWidget *parent, Record * record) : QTabWidget(parent)
{
    _record = record;
    addTab(new MotionDetectorWidget(), tr("Motion Detection"));
}

void RecordWidget::setRecord(Record * record)
{
    _record = record;
    emit recordChanged(record);
}
