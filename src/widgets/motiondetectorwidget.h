#ifndef MOTION_DETECTOR_WIDGET_H
#define MOTION_DETECTOR_WIDGET_H

#include <QPair>
#include <QString>
#include <QWidget>

#include "tools/motiondetector.h"

class AngleSelector;
class AngularMotionPlot;
class QVBoxLayout;
class Record;

class MotionDetectorWidget : public QWidget
{
    Q_OBJECT
    
public:
    MotionDetectorWidget(QWidget * parent = 0);
    
    Record * record() const;
    
public slots:
    void run();
    void setRecord(Record * record);
    void setDefaultAngle(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
protected slots:

signals:
    void recordChanged(Record * record);
    
private:
    QPair<QString, QString> _fixedDefault;
    QVBoxLayout * _layout;
    QPair<QString, QString> _mobileDefault;
    MotionDetector _motionDetector;
    AngularMotionPlot * _plot;
    Record * _record;
    AngleSelector * _angleSelector;
};

#endif // MOTION_DETECTOR_WIDGET_H
