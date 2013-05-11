#include "motiondetectorwidget.h"

#include <QVBoxLayout>
#include <QList>
#include <QString>

#include "tools/motiondetector.h"
#include "utils/record.h"
#include "widgets/angleselector.h"

MotionDetectorWidget::MotionDetectorWidget(QWidget * parent): QWidget(parent)
{
    _layout = new QVBoxLayout();
    setLayout(_layout);
    
    _selector = new AngleSelector();
    _layout->addWidget(_selector);
}

Record * MotionDetectorWidget::record() const
{
    return _record;
}

void MotionDetectorWidget::setRecord(Record * record)
{
    _record = record;
    _detector.setRecord(record);
    _selector->setItems(record->labels());
    
    emit recordChanged(record);
}
