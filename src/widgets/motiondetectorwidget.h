#ifndef MOTION_DETECTOR_WIDGET_H
#define MOTION_DETECTOR_WIDGET_H

#include <QWidget>

#include "tools/motiondetector.h"

class AngleSelector;
class QVBoxLayout;
class Record;

class MotionDetectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    MotionDetectorWidget(QWidget * parent = 0);
    
    Record * record() const;
    
public slots:
    void setRecord(Record * record);
    
protected:

signals:
    void recordChanged(Record * record);
    
private:
    MotionDetector _detector;
    QVBoxLayout * _layout;
    Record * _record;
    AngleSelector * _selector;
};

#endif // MOTION_DETECTOR_WIDGET_H
